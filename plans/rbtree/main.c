#include <stdio.h>
#include "rb_tree.h"

int main()
{
    rbtree *root = NULL;
    int arr[6] = { 1, 6, 7 };
    root = rbtree_add(root, "hook", &arr[0]);
    root = rbtree_add(root, "hok", &arr[1]);
    root = rbtree_add(root, "hoy", &arr[2]);
    arr[3] = *(int *)rbtree_parse_node(rbtree_search(root, "hook"));
    arr[4] = *(int *)rbtree_parse_node(rbtree_search(root, "hok"));
    arr[5] = *(int *)rbtree_parse_node(rbtree_search(root, "hoy"));

    printf("%d %d %d\n", arr[3], arr[4], arr[5]);

    rbtree_destroy(root, 0);
    return 0;
}
