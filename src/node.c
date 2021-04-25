#include "include/node.h"
#include <string.h>
#include <stdarg.h>

node_t* init_node(char* val, int type, unsigned int length){
    node_t* node = malloc(sizeof(node_t));
    node -> type = type;
    node -> val = val;
    node -> child_length = 0;
    node -> length = length;
    node -> block_size = 4;
    node -> children = malloc(4 * sizeof(node_t));
    return node;
}

void node_push(node_t* node, node_t* child){
    node -> child_length++;

    if(node -> child_length % node -> block_size == 0){
        node -> children = realloc(node -> children, sizeof(node_t*) * (node -> child_length + node -> block_size));
        node -> block_size *= 2;
    }

    node -> children[node -> child_length - 1] = child;
}

void node_print(node_t* node, unsigned int depth){
    for(int i = 0; i < depth; i++)
        printf("    ");

    if(node -> type == NODE_OBJECT)
        printf("Object");
    else if(node -> type == NODE_ARRAY)
        printf("Array");
    else
        for(int i = 0; i < node -> length; i++)
            printf("%c", node -> val[i]);
    
    printf("\n");

    for(int i = 0; i < node -> child_length; i++)
        node_print(node -> children[i], depth + 1);
}

void node_free(node_t* node){
    for(int i = 0; i < node -> child_length; i++)
        node_free(node -> children[i]);
    
    free(node -> children);
    free(node);
}

char* node_get_val(node_t* node){
    if(node == NULL)
        return NULL;

    char* val = malloc(node -> length + 1);
    for(int i = 0; i < node -> length; i++)
        val[i] = node -> val[i];
    val[node -> length] = '\0';
    return val;
}

node_t* node_get_by_index(node_t* node, unsigned int i){
    if(node == NULL)
        return NULL;

    if(node -> type == NODE_ID)
        return node_get_by_index(node -> children[0], i);

    if (i > node -> child_length-1)
        return NULL;

    return node -> children[i];
}

node_t* node_get_by_id(node_t* node, char* id){
    if(node == NULL)
        return NULL;

    if(node -> type == NODE_ID)
        return node_get_by_id(node -> children[0], id);

    for(int i = 0; i < node -> child_length; i++){
        char* val = node_get_val(node -> children[i]);

        if(!strcmp(val, id)){
            free(val);
            return node -> children[i];
        }
    
        free(val);
    }

    return NULL;
}