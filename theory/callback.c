#include <stdio.h>
#include <stdlib.h>

/* General profile of callback function:
void callback_function(int num, void *userdata); */

typedef struct tree_tag {
    int val;
    struct tree_tag *left, *right;
} tree;

struct minmaxcount {
    int count, max, min;
};

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

void int_bin_tree_traverse(tree *r,
                           void  (*callback)(int, void*),
                           void *userdata)
{
    if (!r)
        return;
    int_bin_tree_traverse(r->left, callback, userdata);
    (*callback)(r->val, userdata);
    int_bin_tree_traverse(r->right, callback, userdata);
}

void int_callback_print(int data, void *userdata)
{
    printf("%d ", data);
}

void int_callback_sum(int data, void *userdata)
{
    *(int*)userdata += data;
    /* too long:
    int *sum = userdata;
    *sum += data;
    */
}

void int_callback_minmaxcount(int data, void *userdata)
{
    struct minmaxcount *mmc = userdata;
    if (mmc->count == 0)
        mmc->min = mmc->max = data;
    else if (data < mmc->min)
        mmc->min = data;
    else if (data > mmc->max)
        mmc->max = data;
    mmc->count++;
}

int main()
{
    tree *r = NULL;
    int res;
    struct minmaxcount mmc;
    r = int_bin_tree_add(r, 5);
    r = int_bin_tree_add(r, 1);
    r = int_bin_tree_add(r, 8);
    r = int_bin_tree_add(r, 9);
    r = int_bin_tree_add(r, -5);

    int_bin_tree_traverse(r, int_callback_print, NULL);
    res = 0;
    int_bin_tree_traverse(r, int_callback_sum, &res);
    printf("\n%d\n", res);
    mmc.count = 0;
    int_bin_tree_traverse(r, int_callback_minmaxcount, &mmc);
    if (mmc.count)
        printf("c: %d, max: %d, min: %d\n", mmc.count, mmc.max, mmc.min);
    else
        printf("c: %d\n", mmc.count);
    int_bin_tree_erase(r);
    return 0;
}
