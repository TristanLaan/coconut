#include <stddef.h>
#include <stdio.h>
#include "assert.h"

#include "gen_helpers/out_macros.h"
#include "palm/ctinfo.h"
#include "palm/str.h"
#include "ccn/dynamic_core.h"

void *DGFTallocTravData()
{
    return 0;
}

void DGFTfreeTravData(void *data)
{

}

static FILE *fp;
static int indent = 0;
static char *basic_node_type = "node_st";
static char *curr_node_name = NULL;
static char *curr_node_name_upr = NULL;
static int arg_num = 0;
static char *node_type_enum_prefix = "NT_";
static node_st *ast;

node_st *DGFTast(node_st *node)
{
    fp = stdout;
    ast = node;
    TRAVopt(AST_INODES(node));
    return node;
}

node_st *DGFTiactions(node_st *node)
{
    return node;
}

node_st *DGFTiphase(node_st *node)
{
    return node;
}

node_st *DGFTitraversal(node_st *node)
{
    return node;
}

node_st *DGFTipass(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGFTinode(node_st *node)
{
    OUT_START_FUNC("struct ccn_node *DEL%s(struct ccn_node *arg_node)", ID_LWR(INODE_NAME(node)));
    if (INODE_ICHILDREN(node)) {
        OUT_FIELD("TRAVchildren(arg_node)");
    }
    TRAVopt(INODE_IATTRIBUTES(node));
    OUT_FIELD("MEMfree(arg_node->data.N_%s)", ID_LWR(INODE_NAME(node)));
    OUT_FIELD("arg_node = MEMfree(arg_node)");
    OUT_FIELD("return arg_node");
    OUT_END_FUNC();
    TRAVopt(INODE_NEXT(node));
    return node;
}

node_st *DGFTinodeset(node_st *node)
{
    TRAVchildren(node);
    return node;
}

node_st *DGFTchild(node_st *node)
{

    return node;
}

node_st *DGFTattribute(node_st *node)
{

    return node;
}

node_st *DGFTste(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetoperation(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetliteral(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTsetreference(node_st *node)
{

    TRAVchildren(node);
    return node;
}

node_st *DGFTienum(node_st *node)
{
    return node;
}

node_st *DGFTid(node_st *node)
{
    return node;
}