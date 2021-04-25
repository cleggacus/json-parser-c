#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <json_parser/parser.h>

// void lexer(){
//     char token_types[9][18] = {
//         "TOKEN_ID         ",
//         "TOKEN_STRING     ",
//         "TOKEN_COLON      ",
//         "TOKEN_COMMA      ",
//         "TOKEN_LCURLY     ",
//         "TOKEN_RCURLY     ",
//         "TOKEN_LSQUARE    ",
//         "TOKEN_RSQUARE    ",
//         "TOKEN_END        "
//     };

//     char* location = "../examples/test.json";
//     lexer_t lexer = init_lexer(location);

//     while(1){
//         token_t t = lexer_get_next_token(&lexer);

//         if(t.type == TOKEN_END)
//             break;

//         printf("\x1B[35m%s \x1B[32m%s\n", token_types[t.type], t.val);
//     }
// }

void parse(){

    // node_t* a = node_get_by_index(
    //     node_get_by_id(
    //     node_get_by_id(
    //     node_get_by_id(
    //     node_get_by_id(
    //         parser.root_node,
    //     "quiz"),
    //     "sport"),
    //     "q1"),
    //     "options"),
    // 1);
}

int main(){
    // double startTime = (double)clock()/1000;

    FILE* file = fopen("../examples/asset.json", "r");
    fseek(file, 0L, SEEK_END);
    long lSize = ftell(file);
    rewind(file);
    char* contents = malloc(lSize+1);
    contents[lSize] = '\0';
    fread(contents , lSize, 1, file);

    parser_t parser = init_parser(contents);
    parser_parse(&parser);
    parser_print(&parser);

    parser_free(&parser);
    free(contents);

    node_t* n1 = node_get_by_id(parser.root_node, "some_attr");
    node_t* n2 = node_get_by_index(n1, 2);
    char* val = node_get_val(n2);
    free(val);

    // double endTime = (double)clock()/1000;
    // double timeElapsed = endTime - startTime;
    // printf("%f ms\n", timeElapsed);
    return 0;
};