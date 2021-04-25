# JSON parser
Basic JSON parser library made in c


## How to compile and install

```bash
git clone https://github.com/cleggacus/json-parser-c
cd json-parser-c
mkdir bin
cmake ..
sudo make install
```

## How to use

```c
#include <stdlib.h>
#include <stdio.h>
#include <json_parser/parser.h>

int main(){
    // Load file into a char* on heap.

    FILE* file = fopen("../examples/asset.json", "r");
    fseek(file, 0L, SEEK_END);
    long lSize = ftell(file);
    rewind(file);
    char* contents = malloc(lSize+1);
    contents[lSize] = '\0';
    fread(contents , lSize, 1, file);

    // Create parser with contents.
    parser_t parser = init_parser(contents);

    // Parse contents in parser.
    parser_parse(&parser);

    // Print tree of parsed json
    parser_print(&parser);

    // Gets attr from node ( eg. { "some_attr": ... } )
    node_t* n1 = node_get_by_id(parser.root_node, "some_attr");

    // Gets from array from node ( eg. ["1", "2", "3", ...] )
    node_t* n2 = node_get_by_index(n1, 2);

    // Gets val of node
    char* val = node_get_val(n2);

    // Free all memory.
    free(val);
    free(contents);
    parser_free(&parser);

    return 0;
};
```
