#include <stdlib.h>

#include "include/token.h"

token_t init_token(int type, char* val, unsigned int length){
    token_t token;
    token.type = type;
    token.val = val;
    token.length = length;
    return token;
}