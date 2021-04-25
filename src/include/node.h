#ifndef NODE_H
#define NODE_H

#include "lexer.h"

typedef struct NODE_STRUCT {
    enum {
        NODE_ID,
        NODE_STRING,
        NODE_OBJECT,
        NODE_ARRAY
    } type;
    char* val;
    unsigned int length;
    unsigned int child_length;
    unsigned int block_size;
    struct NODE_STRUCT** children;
} node_t;

node_t* init_node(char* val, int type, unsigned int length);
void node_push(node_t* node, node_t* child);
void node_print(node_t* node, unsigned int depth);
void node_free(node_t* node);

char* node_get_val(node_t* node);
node_t* node_get_by_index(node_t* node, unsigned int i);
node_t* node_get_by_id(node_t* node, char* id);
node_t* node_query(node_t* node, unsigned int length, ...);

#endif