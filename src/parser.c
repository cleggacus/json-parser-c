#include "include/parser.h"

parser_t init_parser(char* json){
    parser_t parser;
    parser.lexer = init_lexer(json);
    parser.scope_length = 0;
    parser.awaiting_r_val = false;
    parser.block_size = 4;
    parser.scope_stack = malloc(4 * sizeof(node_t));
    return parser;
}

void parser_parse(parser_t* parser){
    while(1){
        token_t t = lexer_get_next_token(&parser -> lexer);

        if(t.type == TOKEN_END)
            break;
            
        switch(t.type){
            case TOKEN_STRING:{
                if(parser -> awaiting_r_val ){
                    node_t* node = init_node(t.val, NODE_STRING, t.length);
                    node_push(parser_current_scope(parser), node);
                    if(parser_current_scope(parser) -> type == NODE_ID)
                        parser_scope_pop(parser);
                }else{
                    node_t* node = init_node(t.val, NODE_ID, t.length);
                    node_push(parser_current_scope(parser), node);
                    parser_scope_push(parser, node);
                }
                    
                break;
            }
            case TOKEN_COLON:
                parser -> awaiting_r_val = true;
                break;
            case TOKEN_COMMA:
                parser -> awaiting_r_val = parser_current_scope(parser) -> type == NODE_ARRAY;
                break;
            case TOKEN_LCURLY:{
                parser -> awaiting_r_val = false;
                node_t* node = init_node(NULL, NODE_OBJECT, 0);
                if(parser -> scope_length > 0)
                    node_push(parser_current_scope(parser), node);
                parser_scope_push(parser, node);
                break;
            }
            case TOKEN_RCURLY:{
                if(parser_current_scope(parser) -> type == NODE_OBJECT)
                    parser_scope_pop(parser);
                if(parser_current_scope(parser) -> type == NODE_ID)
                    parser_scope_pop(parser);
                break;
            }
            case TOKEN_LSQUARE:{
                node_t* node = init_node(NULL, NODE_ARRAY, 0);
                node_push(parser_current_scope(parser), node);
                parser_scope_push(parser, node);
                break;
            }
            case TOKEN_RSQUARE:{
                if(parser_current_scope(parser) -> type == NODE_ARRAY)
                    parser_scope_pop(parser);
                if(parser_current_scope(parser) -> type == NODE_ID)
                    parser_scope_pop(parser);
                break;
            }
        }
    }
}

void parser_scope_push(parser_t* parser, node_t* child){
    if(parser -> scope_length == 0)
        parser -> root_node = child;

    parser -> scope_length++;

    if(parser -> scope_length % parser -> block_size == 0){
        parser -> scope_stack = realloc(parser -> scope_stack, sizeof(node_t*) * (parser -> scope_length + parser -> block_size));
        parser -> block_size += parser -> block_size;
    }

    parser -> scope_stack[parser -> scope_length - 1] = child;
}

void parser_scope_pop(parser_t* parser){
    if(parser -> scope_length > 0){
        parser -> scope_length--;
    }
}

node_t* parser_current_scope(parser_t* parser){
    return parser -> scope_length <= 0 ?
        parser -> root_node : parser -> scope_stack[parser -> scope_length - 1];
}

void parser_print(parser_t* parser){
    node_print(parser -> root_node, 0);
}

void parser_free(parser_t* parser){
    free(parser -> scope_stack);

    if(parser -> root_node)
        node_free(parser -> root_node);
}