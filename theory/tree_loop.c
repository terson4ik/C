#include <stdio.h>
#include <stdlib.h>

typedef struct tree_tag {
    int val;
    struct tree_tag *left, *right;
} tree;

tree *int_bin_tree_add(tree *r, int x)
{
    if (!r) {
        r = malloc(sizeof(*r));
        if (!r)
            return NULL;
        r->left = r->right = NULL;
        r->val = x;
    } else if (x < r->val) {
        r->left  = int_bin_tree_add(r->left, x);
    } else if (x > r->val) {
        r->right = int_bin_tree_add(r->right, x);
    }
    return r;
}

void int_bin_tree_erase(tree *r)
{
    if (!r)
        return;
    int_bin_tree_erase(r->left);
    int_bin_tree_erase(r->right);
    free(r);
}

void int_bin_tree_print_recs(tree *r)
{
    if (!r)
        return;
    int_bin_tree_print_recs(r->left);
    printf("%d ", r->val);
    int_bin_tree_print_recs(r->right);
}

void int_bin_tree_print_loop(tree *r)
{
    enum states { start, left_visited, finish };
    struct backpath {
        tree *nd;
        enum states st;
        struct backpath *next;
    };
    struct backpath *bp, *t;
    if (!r)
        return;
    bp = malloc(sizeof(*bp));
    bp->nd = r;
    bp->st = start;
    bp->next = NULL;
    while (bp)
        switch(bp->st) {
            case start:
                bp->st = left_visited;
                if (bp->nd->left) {
                    t = malloc(sizeof(*bp));
                    t->nd = bp->nd->left;
                    t->st = start;
                    t->next = bp;
                    bp = t;
                    continue;
                }
                /* no break here */
            case left_visited:
                bp->st = finish;
                printf("%d ", bp->nd->val);
                if (bp->nd->right) {
                    t = malloc(sizeof(*bp));
                    t->nd = bp->nd->right;
                    t->st = start;
                    t->next = bp;
                    bp = t;
                    continue;
                }
                /* no break here */
            case finish:
                t = bp;
                bp = bp->next;
                free(t);
        }
}

int main()
{
    tree *r = NULL;
    r = int_bin_tree_add(r, 5);
    r = int_bin_tree_add(r, 1);
    r = int_bin_tree_add(r, 8);
    r = int_bin_tree_add(r, 9);
    r = int_bin_tree_add(r, -5);

    int_bin_tree_print_recs(r);
    putchar('\n');

    int_bin_tree_print_loop(r);
    putchar('\n');

    int_bin_tree_erase(r);
    return 0;
}
