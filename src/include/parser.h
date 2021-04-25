#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "lexer.h"
#include "node.h"

typedef struct PARSER_STRUCT {
    lexer_t lexer;
    node_t* root_node;
    bool awaiting_r_val;
    unsigned int scope_length;
    unsigned int block_size;
    node_t** scope_stack;
} parser_t;

parser_t init_parser(char* json);
void parser_parse(parser_t* parser);

void parser_scope_push(parser_t* parser, node_t* child);
void parser_scope_pop(parser_t* parser);
node_t* parser_current_scope(parser_t* parser);
void parser_print(parser_t* parser);
void parser_free(parser_t* parser);

#endif