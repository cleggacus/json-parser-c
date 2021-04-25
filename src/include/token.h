#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT {
    enum {
        TOKEN_STRING,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LCURLY,
        TOKEN_RCURLY,
        TOKEN_LSQUARE,
        TOKEN_RSQUARE,
        TOKEN_END
    } type;

    char* val;
    unsigned int length;
} token_t;

token_t init_token(int type, char* val, unsigned int length);

#endif