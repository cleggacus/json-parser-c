#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "include/lexer.h"

#define ADVANCE(lexer) if(lexer -> c[0] != '\0') lexer -> c++;
#define STRING_BLOCK_SIZE 32

lexer_t init_lexer(char* json){
    lexer_t lexer;

    lexer.contents = json;
    lexer.c = lexer.contents;

    return lexer;
}

token_t lexer_get_next_token(lexer_t* lexer){
    while(lexer -> c[0] <= 32 && lexer -> c[0] > 0)
        ADVANCE(lexer);

    char* c = lexer -> c;

    if(c[0] == '\0')
        return init_token(TOKEN_END, NULL, 0);
    

    switch (c[0]){
        case '"':
            return lexer_collect_string(lexer);
            break;
        case ':':
            ADVANCE(lexer);
            return init_token(TOKEN_COLON, c, 1);
            break;
        case ',':
            ADVANCE(lexer);
            return init_token(TOKEN_COMMA, c, 1);
            break;
        case '{':
            ADVANCE(lexer);
            return init_token(TOKEN_LCURLY, c, 1);
            break;
        case '}':
            ADVANCE(lexer);
            return init_token(TOKEN_RCURLY, c, 1);
            break;
        case '[':
            ADVANCE(lexer);
            return init_token(TOKEN_LSQUARE, c, 1);
            break;
        case ']':
            ADVANCE(lexer);
            return init_token(TOKEN_RSQUARE, c, 1);
            break;
    }
    
    return lexer_collect_token(lexer);
}

token_t lexer_collect_token(lexer_t* lexer){
    unsigned int length = 0;
    char* start = lexer -> c;

    while(
        lexer -> c[0] != '}' &&
        lexer -> c[0] != ',' &&
        lexer -> c[0] != ']' &&
        lexer -> c[0] != ':'
    ){
        length++;
        ADVANCE(lexer);
    };

    return init_token(TOKEN_STRING, start, length);
}

token_t lexer_collect_string(lexer_t* lexer){
    ADVANCE(lexer);

    unsigned int length = 0;
    char* start = lexer -> c;

    bool escape = false;

    while(lexer -> c[0] != '"' || escape){
        if(escape)
            escape = false;

        length++;
        ADVANCE(lexer);

        if(lexer -> c[0] == '\\' && !escape)
            escape = true;
    }

    ADVANCE(lexer);

    return init_token(TOKEN_STRING, start, length);
}