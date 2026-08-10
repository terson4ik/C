#include <stdio.h>
#include <stdlib.h>
#include "other.h" /* strtoi */
#include "tree.h"

#define DEFAULT_SIZE    6
#define BUF_SIZE        4096

int main(int argc, char **argv)
{
    char *inp_str = malloc(BUF_SIZE);
    prefix_tree *root = NULL;
    const int prefix_size = (argv[1] && argv[1][0] == '-') ? 
                                                strtoi(argv[1] + 1) 
                                                :
                                                DEFAULT_SIZE;
    if (prefix_size <= 0) { /* strtoi give negative if not digit */
        fputs("Incorrect flag. Example of use ./program -6\n", stderr);
        return 1;
    }

    while (getword(inp_str, BUF_SIZE) != EOF)
        if (is_alpha(*inp_str))
            root = prefix_tree_add(root, inp_str, prefix_size);
    prefix_tree_print(root);

    prefix_tree_erase(root);
    free(inp_str);
    return 0;
}
