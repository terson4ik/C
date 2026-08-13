#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"
#include "tree.h"
#include "sort.h"

#define BUF_SIZE 4096

int main()
{
    char *buf = malloc(BUF_SIZE);
    word_count *arr;
    int size_arr;
    tree_word *root = NULL;
    if (!buf)
        return 1;

    while (get_word(buf, BUF_SIZE) != EOF)
        if (isalpha(*buf))
            root = tree_word_add(root, buf);

    size_arr = tree_word_size(root);
    arr = malloc(size_arr * sizeof(*arr));
    convert_tree_to_arr(root, arr);
    quick_sort(arr, 0, size_arr, UP);
    shell_sort(arr, size_arr, DOWN);
    print_word_arr(arr, size_arr);

    tree_word_erase(root);
    free(arr);
    free(buf);
    return 0;
}
