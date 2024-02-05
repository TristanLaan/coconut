/**
 * @file
 *
 * generate visit
 *
 *
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "frontend/attribute_scheduler/common.h"
#include "frontend/attribute_scheduler/fill_visit_stubs.h"
#include "frontend/attribute_scheduler/generate_visits.h"
#include "frontend/attribute_scheduler/graph.h"
#include "frontend/attribute_scheduler/queue.h"
#include "frontend/ctihelp.h"
#include "frontend/symboltable.h"
#include "globals.h"
#include "palm/ctinfo.h"
#include "palm/hash_table.h"
#include "palm/memory.h"
#include "palm/str.h"

static const int htable_size = 200;

static FILE *log = NULL;

struct dependency {
    struct GRnode *dependency;
    struct dependency *next;
};

void free_visits(struct visits *visits) {
    for (size_t i = 0; i < visits->length; ++i) {
        struct visit *visit = visits->visits[i];
        MEMfree(visit->inputs);
        MEMfree(visit->outputs);
        MEMfree(visit);
    }

    MEMfree(visits);
}

struct child_visit {
    node_st *child;
    struct visit *visit;
};

static size_t hash_child_visit(void *ptr) {
    struct child_visit *key = (struct child_visit *)ptr;

    size_t hkey_child = (((size_t)key->child >> 5) & 0x1f);
    size_t hkey_visit = (((size_t)key->visit >> 5) & 0x1f);

    return hkey_child + hkey_visit;
}

static inline bool child_visit_equal(struct child_visit *ptr1,
                                     struct child_visit *ptr2) {
    return ptr1->child == ptr2->child && ptr1->visit == ptr2->visit;
}

static bool hash_child_visit_equal(void *ptr1, void *ptr2) {
    return child_visit_equal((struct child_visit *)ptr1,
                             (struct child_visit *)ptr2);
}

static inline struct child_visit *
get_child_visit(htable_st *htable, node_st *child, struct visit *visit) {
    struct child_visit lookup = {.child = child, .visit = visit};
    struct child_visit *child_visit =
        (struct child_visit *)HTlookup(htable, &lookup);
    if (child_visit) {
        return child_visit;
    }
    child_visit = MEMmalloc(sizeof(struct child_visit));
    child_visit->child = child;
    child_visit->visit = visit;
    HTinsert(htable, child_visit, child_visit);
    return child_visit;
}

static void *free_child_visit_htable(void *item) {
    struct child_visit *child_visit = (struct child_visit *)item;
    MEMfree(child_visit);
    return NULL;
}

static void *free_dependencies_htable(void *item) {
    struct dependency *dependency = (struct dependency *)item;
    while (dependency) {
        struct dependency *next = dependency->next;
        MEMfree(dependency);
        dependency = next;
    }
    return NULL;
}

static inline char *node_to_str(struct GRnode *node) {
    return STRfmt("%s.%s", ID_LWR(get_node_name(node->node)),
                  ID_LWR(ATTRIBUTE_NAME(node->attribute)));
}

static struct dependency *find_dependencies(graph_st *graph,
                                            struct GRnode *node) {
    struct dependency *deps = NULL;

    for (struct GRnode *dep_node = graph->nodes; dep_node;
         dep_node = dep_node->next) {
        if (dep_node == node) {
            continue;
        }

        if (GRlookup_edge(graph, dep_node, node)) {
            struct dependency *dep = MEMmalloc(sizeof(struct dependency));
            dep->dependency = dep_node;
            dep->next = deps;
            deps = dep;

            char *dep_node_name = node_to_str(dep_node);
            char *to_node_name = node_to_str(node);
            fprintf(log, "Found dependency from %s to %s\n", dep_node_name, to_node_name);
            MEMfree(dep_node_name);
            MEMfree(to_node_name);
        }
    }

    return deps;
}

static long find_visit(struct visits *visits, struct GRnode *node) {
    for (size_t i = 0; i < visits->length; ++i) {
        struct visit *visit = visits->visits[i];
        for (size_t j = 0; j < visit->outputs_length; ++j) {
            if (visit->outputs[j]->attribute == node->attribute) {
                return (long)visit->index;
            }
        }
    }

    return -1;
}

struct seq_queue_item {
    bool is_visit;
    union {
        struct GRnode *node;
        struct child_visit *visit;
    };
};

static inline void sched_equation_dependency(node_st *node, node_st *st,
                                             struct GRnode *dependency,
                                             htable_st *visits_htable,
                                             htable_st *child_visits_htable,
                                             htable_st *queued,
                                             queue_st *queue) {
    node_st *dep_node = dependency->node;
    node_st *dep_attr = dependency->attribute;

    // Node is generated by external visit
    if (dep_node != node && ATTRIBUTE_IS_SYNTHESIZED(dep_attr)) {
        struct visits *visits =
            HTlookup(visits_htable, get_node_type(dep_node, st));
        assert(visits != NULL);
        long visit_index = find_visit(visits, dependency);
        assert(visit_index != -1);
        struct visit *visit = visits->visits[visit_index];
        assert(NODE_TYPE(dep_node) == NT_CHILD);
        struct child_visit *child_visit =
            get_child_visit(child_visits_htable, dep_node, visit);
        if (!HTlookup(queued, child_visit)) {
            struct seq_queue_item *new_item =
                MEMmalloc(sizeof(struct seq_queue_item));
            new_item->is_visit = true;
            new_item->visit = child_visit;
            fprintf(log, "Unscheduled dependency visit %s %lu, adding to "
                   "queue\n",
                   ID_LWR(CHILD_NAME(dep_node)), visit->index);
            QUinsert(queue, new_item);
            HTinsert(queued, visit, (void *)1);
        }
    } else { // Normal dependency
        if (!HTlookup(queued, dependency)) {
            struct seq_queue_item *new_item =
                MEMmalloc(sizeof(struct seq_queue_item));
            new_item->is_visit = false;
            new_item->node = dependency;
            char *node_name = node_to_str(new_item->node);
            fprintf(log, "Unscheduled dependency attribute %s, "
                    "adding to queue\n", node_name);
            MEMfree(node_name);
            QUinsert(queue, new_item);
            HTinsert(queued, dependency, (void *)1);
        }
    }
}

static bool sched_visit_dependencies(graph_st *graph, node_st *node,
                                     node_st *st,
                                     struct child_visit *child_visit,
                                     htable_st *visits_htable,
                                     htable_st *child_visits_htable,
                                     htable_st *scheduled, htable_st *queued,
                                     queue_st *queue) {
    bool has_unscheduled_dependencies = false;
    struct visits *visits =
        HTlookup(visits_htable, get_node_type(child_visit->child, st));
    struct visit *visit = child_visit->visit;
    // Check previous visits
    for (size_t i = 0; i < visit->index; ++i) {
        struct child_visit *prev_child_visit = get_child_visit(
            child_visits_htable, child_visit->child, visits->visits[i]);
        if (HTlookup(scheduled, prev_child_visit)) {
            continue;
        }

        has_unscheduled_dependencies = true;

        if (!HTlookup(queued, prev_child_visit)) {
            struct seq_queue_item *new_item =
                MEMmalloc(sizeof(struct seq_queue_item));
            new_item->is_visit = true;
            new_item->visit = prev_child_visit;
            fprintf(log, "Unscheduled dependency visit %s %lu, adding to "
                   "queue\n",
                   ID_LWR(CHILD_NAME(prev_child_visit->child)),
                   prev_child_visit->visit->index);
            QUinsert(queue, new_item);
            HTinsert(queued, prev_child_visit, (void *)1);
        }
    }

    // Check visit inputs
    for (size_t i = 0; i < visit->inputs_length; ++i) {
        struct GRnode *input = visit->inputs[i];
        struct GRnode *gnode =
            GRlookup_node(graph, child_visit->child, input->attribute);

        if (HTlookup(scheduled, gnode)) {
            continue;
        }

        has_unscheduled_dependencies = true;
        sched_equation_dependency(node, st, gnode, visits_htable,
                                  child_visits_htable, queued, queue);
    }

    return has_unscheduled_dependencies;
}

static bool sched_equation_dependencies(
    node_st *node, node_st *st, struct GRnode *gnode, htable_st *visits_htable,
    htable_st *child_visits_htable, htable_st *dependencies,
    htable_st *scheduled, htable_st *queued, queue_st *queue) {
    bool has_unscheduled_dependencies = false;
    // Check equation dependencies
    for (struct dependency *dep = HTlookup(dependencies, gnode); dep;
         dep = dep->next) {
        if (HTlookup(scheduled, dep->dependency)) {
            continue;
        }
        char *dep_name = node_to_str(dep->dependency);
        fprintf(log, "Found Unscheduled dependency %s\n", dep_name);
        MEMfree(dep_name);

        has_unscheduled_dependencies = true;
        sched_equation_dependency(node, st, dep->dependency, visits_htable,
                                  child_visits_htable, queued, queue);
    }

    return has_unscheduled_dependencies;
}

static inline bool check_scheduled(htable_st *scheduled,
                                   struct seq_queue_item *item) {
    if (item->is_visit) {
        return HTlookup(scheduled, item->visit);
    } else {
        return HTlookup(scheduled, item->node);
    }
}

static inline bool mark_scheduled(graph_st *graph, htable_st *scheduled,
                                  struct seq_queue_item *item) {
    if (item->is_visit) {
        struct child_visit *child_visit = item->visit;
        // Mark visit outputs as scheduled
        for (size_t i = 0; i < child_visit->visit->outputs_length; ++i) {
            struct GRnode *output =
                GRlookup_node(graph, child_visit->child,
                              child_visit->visit->outputs[i]->attribute);
            HTinsert(scheduled, output, (void *)1);
        }
        return HTinsert(scheduled, item->visit, (void *)1);
    } else {
        return HTinsert(scheduled, item->node, (void *)1);
    }
}

static inline void set_alt(node_st *sequence, node_st *alt) {
    switch (NODE_TYPE(sequence))
    {
    case NT_VISIT_SEQUENCE_VISIT:
        VISIT_SEQUENCE_VISIT_ALT(sequence) = alt;
        break;
    case NT_VISIT_SEQUENCE_DUMMY:
        VISIT_SEQUENCE_DUMMY_ALT(sequence) = alt;
        break;
    default:
        assert(false);
        break;
    }
}

static node_st *add_visit_sequence_visit_nodeset_rec(
    node_st **visit_tail, node_st *st, htable_st *visits_htable,
    htable_st *visit_stubs_htable, node_st *expr, node_st *child,
    struct visit *original_visit) {
    if (expr == NULL) {
        return NULL;
    }

    assert(NODE_TYPE(expr) == NT_SETLITERAL);

    node_st *node = STlookup(st, SETLITERAL_REFERENCE(expr));
    struct visits *visits = HTlookup(visits_htable, node);
    node_st *sequence = NULL;
    if (original_visit->index < visits->length) {
        struct visit *visit = visits->visits[original_visit->index];

        sequence = ASTvisit_sequence_visit(child, NULL);
        add_visit_stub(visit_stubs_htable, visit, sequence);
    } else {
        fprintf(log, "Do not add visit %s %lu for type %s\n", ID_LWR(get_node_name(child)), original_visit->index, ID_LWR(get_node_name(node)));
        sequence = ASTvisit_sequence_dummy(node);
    }

    node_st *left_tail = NULL;
    node_st *sequence_left = add_visit_sequence_visit_nodeset_rec(
        &left_tail, st, visits_htable, visit_stubs_htable,
        SETLITERAL_LEFT(expr), child, original_visit);
    set_alt(sequence, sequence_left);

    node_st *right_tail = NULL;
    node_st *sequence_right = add_visit_sequence_visit_nodeset_rec(
        &right_tail, st, visits_htable, visit_stubs_htable,
        SETLITERAL_RIGHT(expr), child, original_visit);
    if (left_tail != NULL) {
        set_alt(left_tail, sequence_right);
    } else {
        set_alt(sequence, sequence_right);
    }

    if (right_tail != NULL) {
        *visit_tail = right_tail;
    } else if (left_tail != NULL) {
        *visit_tail = left_tail;
    } else {
        *visit_tail = sequence;
    }

    return sequence;
}

static inline node_st *
add_visit_sequence_visit_nodeset(node_st *st, htable_st *visits_htable,
                                 htable_st *visit_stubs_htable, node_st *expr,
                                 node_st *child, struct visit *original_visit) {
    node_st *visit_tail = NULL;
    return add_visit_sequence_visit_nodeset_rec(&visit_tail, st, visits_htable,
                                                visit_stubs_htable, expr, child,
                                                original_visit);
}

static void add_visit_sequence(node_st **visit_head, node_st **visit_tail,
                               node_st *st, node_st *node,
                               htable_st *visits_htable,
                               htable_st *visit_stubs_htable,
                               struct seq_queue_item *item) {
    node_st *sequence;
    if (item->is_visit) {
        fprintf(log, "Visiting visit %s %lu\n",
               ID_LWR(CHILD_NAME(item->visit->child)),
               item->visit->visit->index);
        // Actual visit will be added later
        node_st *child = item->visit->child;
        if (CHILD_TYPE(child) == CT_inodeset) {
            node_st *nodeset = get_node_type(child, st);
            sequence = add_visit_sequence_visit_nodeset(
                st, visits_htable, visit_stubs_htable, INODESET_EXPR(nodeset),
                child, item->visit->visit);
        } else {
            sequence = ASTvisit_sequence_visit(child, NULL);
            add_visit_stub(visit_stubs_htable, item->visit->visit, sequence);
        }
    } else {
        struct GRnode *gnode = item->node;
        char *node_name = node_to_str(gnode);
        fprintf(log, "Evaluating attribute %s", node_name);
        // Will be generated by visit
        if (gnode->node != node && ATTRIBUTE_IS_SYNTHESIZED(gnode->attribute)) {
            fprintf(log, "; generated by visit, skipping...\n");
            return;
        }
        fprintf(log, "\n");

        node_st *reference = ASTattribute_reference();
        if (gnode->node != node) {
            ATTRIBUTE_REFERENCE_INODE(reference) =
                CCNcopy(get_node_name(gnode->node));
        }
        ATTRIBUTE_REFERENCE_IATTRIBUTE(reference) =
            CCNcopy(ATTRIBUTE_NAME(gnode->attribute));
        ATTRIBUTE_REFERENCE_REFERENCE(reference) = gnode->attribute;
        ATTRIBUTE_REFERENCE_NODE_TYPE(reference) =
            CCNcopy(get_node_name(get_node_type(gnode->node, st)));

        sequence = ASTvisit_sequence_eval(reference);
    }

    if (sequence == NULL) {
        return;
    }

    if (*visit_head == NULL) {
        *visit_head = sequence;
        *visit_tail = sequence;
    } else {
        if (NODE_TYPE(*visit_tail) == NT_VISIT_SEQUENCE_VISIT) {
            VISIT_SEQUENCE_VISIT_NEXT(*visit_tail) = sequence;
        } else {
            assert(NODE_TYPE(*visit_tail) == NT_VISIT_SEQUENCE_EVAL);
            VISIT_SEQUENCE_EVAL_NEXT(*visit_tail) = sequence;
        }

        *visit_tail = sequence;
    }
}

static node_st *generate_visit(graph_st *graph, node_st *node, node_st *st,
                               htable_st *visits_htable,
                               htable_st *child_visits_htable,
                               htable_st *dependencies, htable_st *scheduled,
                               htable_st *visit_stubs_htable,
                               struct visit *visit, bool last_visit) {
    queue_st *queue = QUcreate();
    htable_st *queued = HTnew_Ptr(htable_size);
    node_st *visit_head = NULL;
    node_st *visit_tail = NULL;
    struct seq_queue_item *item;

    // Insert outputs in queue
    for (size_t i = 0; i < visit->outputs_length; ++i) {
        item = MEMmalloc(sizeof(struct seq_queue_item));
        item->is_visit = false;
        item->node = visit->outputs[i];
        char *node_name = node_to_str(item->node);
        fprintf(log, "Adding visit output %s to queue\n", node_name);
        MEMfree(node_name);
        QUinsert(queue, item);
        HTinsert(queued, item->node, (void *)1);
    }

    // Insert child visits in queue
    for (node_st *child = INODE_ICHILDREN(node); child; child = CHILD_NEXT(child)) {
        struct visits *child_visits = HTlookup(visits_htable, get_node_type(child, st));
        assert(child_visits != NULL);
        size_t stop = last_visit ? child_visits->length : MIN(visit->index + 1, child_visits->length);
        for (size_t i = 0; i < stop; ++i) {
            assert(i < child_visits->length);
            item = MEMmalloc(sizeof(struct seq_queue_item));
            item->is_visit = true;
            item->visit = MEMmalloc(sizeof(struct child_visit));
            item->visit->visit = child_visits->visits[i];
            item->visit->child = child;
            fprintf(log, "Adding child visit %s %lu to queue\n", ID_LWR(CHILD_NAME(child)), child_visits->visits[i]->index);
            QUinsert(queue, item);
            HTinsert(queued, item->visit, (void *)1);
        }
    }

    // Mark inputs as computed
    for (size_t i = 0; i < visit->inputs_length; ++i) {
        if (!HTlookup(scheduled, visit->inputs[i])) {
            HTinsert(scheduled, visit->inputs[i], (void *)1);
        }
    }

    size_t iterations = 0;
    while ((item = QUpop(queue)) != NULL) {
        if (check_scheduled(scheduled, item)) {
            MEMfree(item);
            continue;
        }

        if (iterations >= globals.ag_scheduler_max_iter) {
            struct ctinfo info;
            id_to_info(get_node_name(node), &info);
            char *scheduled_attributes = STRnull();
            char *unscheduled_attributes = STRnull();
            for (struct GRnode *check_node = graph->nodes; check_node;
                 check_node = check_node->next) {
                char *new;
                char *tmp = STRfmt(
                    "  * %s.%s\n", ID_LWR(get_node_name(check_node->node)),
                    ID_LWR(ATTRIBUTE_NAME(check_node->attribute)));
                if (HTlookup(scheduled, check_node)) {
                    new = STRcat(scheduled_attributes, tmp);
                    MEMfree(scheduled_attributes);
                    scheduled_attributes = new;
                } else {
                    new = STRcat(unscheduled_attributes, tmp);
                    MEMfree(unscheduled_attributes);
                    unscheduled_attributes = new;
                }
                MEMfree(tmp);
            }
            char *queued_elements = STRnull();
            do {
                char *tmp, *new;
                if (item->is_visit) {
                    tmp = STRfmt("  * visit %s %lu\n",
                                 ID_LWR(CHILD_NAME(item->visit->child)),
                                 item->visit->visit->index);
                } else {
                    tmp = STRfmt("  * attribute %s.%s\n",
                                 ID_LWR(get_node_name(item->node->node)),
                                 ID_LWR(ATTRIBUTE_NAME(item->node->attribute)));
                }
                new = STRcat(queued_elements, tmp);
                MEMfree(queued_elements);
                queued_elements = new;
                MEMfree(tmp);
            } while ((item = QUpop(queue)) != NULL);

            CTIobj(CTI_ERROR, false, info,
                   "Loop detected in attribute scheduling for node %s.\n"
                   "Scheduler has been running for %lu iterations.\n"
                   "You can increase the max iterations using "
                   "--ag-scheduler-max-iter.\n"
                   "Debug information:\n"
                   "- Scheduled attributes\n%s"
                   "- Unscheduled attributes\n%s"
                   "- Queued elements\n%s",
                   ID_ORIG(INODE_NAME(node)), iterations, scheduled_attributes,
                   unscheduled_attributes, queued_elements);
            MEMfree(scheduled_attributes);
            MEMfree(unscheduled_attributes);
            MEMfree(queued_elements);
            fclose(log);
            CTIabortCompilation();
        }
        iterations += 1;

        bool has_unscheduled_dependencies;
        if (item->is_visit) {
            fprintf(log, "Considering visit %s %lu\n",
                   ID_LWR(CHILD_NAME(item->visit->child)),
                   item->visit->visit->index);
            has_unscheduled_dependencies = sched_visit_dependencies(
                graph, node, st, item->visit, visits_htable,
                child_visits_htable, scheduled, queued, queue);
        } else {
            char *node_name = node_to_str(item->node);
            fprintf(log, "Considering attribute %s\n", node_name);
            MEMfree(node_name);
            has_unscheduled_dependencies = sched_equation_dependencies(
                node, st, item->node, visits_htable, child_visits_htable,
                dependencies, scheduled, queued, queue);
        }

        if (has_unscheduled_dependencies) {
            fprintf(log, "Found unscheduled dependency, skipping...\n");
            QUinsert(queue, item);
        } else {
            fprintf(log, "No unscheduled dependency, adding visit sequence\n");
            mark_scheduled(graph, scheduled, item);
            add_visit_sequence(&visit_head, &visit_tail, st, node,
                               visits_htable, visit_stubs_htable, item);
            MEMfree(item);
        }
    }

    QUdelete(queue);
    HTdelete(queued);

    return visit_head;
}

static inline node_st *generate_visit_input(node_st *node, node_st *st,
                                            struct visit *visit) {
    node_st *input_head = NULL;
    for (long i = visit->inputs_length - 1; i >= 0; --i) {
        node_st *attribute = ASTattribute_reference();
        if (visit->inputs[i]->node != node) {
            ATTRIBUTE_REFERENCE_INODE(attribute) =
                CCNcopy(get_node_name(visit->inputs[i]->node));
        }
        ATTRIBUTE_REFERENCE_IATTRIBUTE(attribute) =
            CCNcopy(ATTRIBUTE_NAME(visit->inputs[i]->attribute));
        ATTRIBUTE_REFERENCE_REFERENCE(attribute) = visit->inputs[i]->attribute;
        ATTRIBUTE_REFERENCE_NODE_TYPE(attribute) =
            CCNcopy(get_node_name(get_node_type(visit->inputs[i]->node, st)));
        node_st *input = ASTvisit_arg_list(attribute);
        VISIT_ARG_LIST_NEXT(input) = input_head;
        input_head = input;
    }

    return input_head;
}

static inline node_st *generate_visit_output(node_st *node, node_st *st,
                                             struct visit *visit) {
    node_st *output_head = NULL;
    for (long i = visit->outputs_length - 1; i >= 0; --i) {
        node_st *attribute = ASTattribute_reference();
        if (visit->outputs[i]->node != node) {
            ATTRIBUTE_REFERENCE_INODE(attribute) =
                CCNcopy(get_node_name(visit->outputs[i]->node));
        }
        ATTRIBUTE_REFERENCE_IATTRIBUTE(attribute) =
            CCNcopy(ATTRIBUTE_NAME(visit->outputs[i]->attribute));
        ATTRIBUTE_REFERENCE_REFERENCE(attribute) = visit->outputs[i]->attribute;
        ATTRIBUTE_REFERENCE_NODE_TYPE(attribute) =
            CCNcopy(get_node_name(get_node_type(visit->outputs[i]->node, st)));
        node_st *output = ASTvisit_arg_list(attribute);
        VISIT_ARG_LIST_NEXT(output) = output_head;
        output_head = output;
    }

    return output_head;
}

node_st *generate_visits(graph_st *graph, node_st *node, node_st *st,
                         htable_st *visits_htable,
                         htable_st *visit_mdata_htable,
                         htable_st *visit_stubs_htable, FILE *log_file) {
    log = log_file;

    node_st *visits_head = NULL;
    node_st *visits_tail = NULL;
    htable_st *scheduled = HTnew_Ptr(htable_size);
    htable_st *dependencies = HTnew_Ptr(htable_size);
    struct visits *visits = HTlookup(visits_htable, node);
    htable_st *child_visits =
        HTnew(htable_size, hash_child_visit, hash_child_visit_equal);

    fprintf(log, "## looking up dependencies\n");
    for (struct GRnode *gnode = graph->nodes; gnode; gnode = gnode->next) {
        struct dependency *deps = find_dependencies(graph, gnode);
        HTinsert(dependencies, gnode, deps);
    }

    fprintf(log, "## Start generating visits\n");
    for (size_t i = 0; i < visits->length; ++i) {
        fprintf(log, "# visit %lu\n", i);
        node_st *visit = generate_visit(graph, node, st, visits_htable,
                                        child_visits, dependencies, scheduled,
                                        visit_stubs_htable, visits->visits[i],
                                        (i + 1) == visits->length);
        node_st *visits_node = ASTvisit(
            visit, generate_visit_input(node, st, visits->visits[i]),
            generate_visit_output(node, st, visits->visits[i]), node, i + 1);
        if (visits_head == NULL) {
            visits_head = visits_node;
            visits_tail = visits_node;
        } else {
            VISIT_NEXT(visits_tail) = visits_node;
            visits_tail = visits_node;
        }

        HTinsert(visit_mdata_htable, visits_node, visits->visits[i]);
        fprintf(log, "\n");
    }
    fprintf(log, "## Finished generating visits\n");

    HTmap(child_visits, free_child_visit_htable);
    HTdelete(child_visits);
    HTdelete(scheduled);
    HTmap(dependencies, free_dependencies_htable);
    HTdelete(dependencies);

    log = NULL;
    return visits_head;
}
