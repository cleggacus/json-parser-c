#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdio.h>

#include "token.h"

typedef struct LEXER_STRUCT {
    char* c;
    char* contents;
} lexer_t;

lexer_t init_lexer(char* json);
void lexer_advance(lexer_t* lexer);
token_t lexer_get_next_token(lexer_t* lexer);
token_t lexer_collect_string(lexer_t* lexer);
token_t lexer_collect_token(lexer_t* lexer);
char* lexer_get_current_char_as_string(lexer_t* lexer);

#endif