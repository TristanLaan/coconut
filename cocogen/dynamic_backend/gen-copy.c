#include <stdio.h>
#include <string.h>

#include "ast/ast.h"
#include "filegen/driver.h"
#include "filegen/genmacros.h"
#include "filegen/util.h"
#include "gen-functions.h"

static int indent = 0;

void gen_init_arguments(Config *config, FILE *fp, Node *node) {
    for (int i = 0; i < array_size(node->children); ++i) {
        Child *child = (Child *)array_get(node->children, i);
        if (child->construct) {
            if (i > 0) {
                out(", ");
            }
            out("NULL");
        }
    }
    for (int i = 0; i < array_size(node->attrs); ++i) {
        Attr *attr = (Attr *)array_get(node->attrs, i);
        if (attr->construct) {
            if ((i == 0 && node->children > 0) || i > 0) {
                out(", ");
            }
            out("%s", attr_default_value(config, fp, attr->type));
        }
    }
}

void gen_copy_func(Config *config, FILE *fp, Node *node) {
    out_start_func("Node *ccn_copy_%s(Node *arg_node)", node->id->lwr);
    out("    Node *new_node = node_init_%s(", node->id->lwr);
    gen_init_arguments(config, fp, node);
    out(");\n");
    for (int i = 0; i < array_size(node->attrs); i++) {
        Attr *attr = array_get(node->attrs, i);
        char *copyfunc;
        if (attr->type == AT_string) {
            copyfunc = "ccn_str_cpy";
        } else if (attr->type == AT_link) {
            copyfunc = "node_copy";
        } else {
            out_field("%s_%s(new_node) = %s_%s(arg_node)", node->id->upr,
                      attr->id->upr, node->id->upr, attr->id->upr);
            continue;
        }
        out_field("%s_%s(new_node) = %s(%s_%s(arg_node))", node->id->upr,
                  attr->id->upr, copyfunc, node->id->upr, attr->id->upr);
    }
    if (node->children) {
        out_field("arg_node = trav_children(arg_node)");
    }
    out_field("return new_node");
    out_end_func();
}

void gen_copy_src(Config *config, FILE *fp) {
    out("#include \"ccn/trav_core.h\"\n");
    out("#include \"ccn/ast_core.h\"\n");
    out("#include \"lib/str.h\"\n");
    out("\n");
    for (int i = 0; i < array_size(config->nodes); ++i) {
        Node *node = array_get(config->nodes, i);
        gen_copy_func(config, fp, node);
    }
}