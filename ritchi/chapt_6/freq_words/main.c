#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getw.h"
#include "tree.h"

#define BUFF_SIZE 1024

int main()
{
    char *buf = malloc(BUFF_SIZE);
    struct tnode *root = NULL;

    while (getword(buf, BUFF_SIZE) != EOF)
        if (isalpha(*buf))
            root = addtree(root, buf);

    treeprint(root);

    erase_tree(root);
    free(buf);
    return 0;
}
