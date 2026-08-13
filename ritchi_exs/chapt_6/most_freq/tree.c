#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "strs.h"

struct tree_word_tag {
    void *word;
    unsigned int counter;
    struct tree_word_tag *left, *right;
}; /* type_def in header file (as API) */

static tree_word *tree_word_new();
tree_word *tree_word_add(tree_word *r, char *word)
{
    int cond;
    if (!r) {
        r = tree_word_new();
        r->counter = 1;
        r->word = str_dup(word);
        return r;
    }
    cond = str_cmp(word, r->word);
    if (cond < 0)
        r->left = tree_word_add(r->left, word);
    else if (cond > 0)
        r->right = tree_word_add(r->right, word);
    else /* cond == 0 */
        r->counter++;
    
    return r;
}

int tree_word_size(tree_word *r)
{
    int akum = 0;
    if (!r)
        return akum;
    if (r->left)
        akum += tree_word_size(r->left);
    if (r->right)
        akum += tree_word_size(r->right);
    akum++;
    return akum;
}

static void convert_help_tree_to_arr(tree_word *r, word_count arr[], int *i);
void convert_tree_to_arr(tree_word *r, word_count arr[])
{
    int i = 0;
    convert_help_tree_to_arr(r, arr, &i);
}

void print_word_arr(word_count arr[], int size)
{
    while (size-- >= 1) {
        printf("%-4d: %s\n", arr->count, arr->word);
        arr++;
    }
}

void tree_word_erase(tree_word *r)
{
    if (!r)
        return;

    if (r->left)
        tree_word_erase(r->left);
    if (r->right)
        tree_word_erase(r->right);

    free(r->word);
    free(r);
}

static tree_word *tree_word_new()
{
    tree_word *new = malloc(sizeof(tree_word));   
    if (!new)
        return NULL;
    new->word = NULL;
    new->counter = 0;
    new->left = new->right = NULL;
    return new;
}

static void convert_help_tree_to_arr(tree_word *r, word_count arr[], int *i)
{
    if (!r)
        return;
    (arr[*i]).word = r->word;
    (arr[*i]).count = r->counter;
    if (r->left) {
        ++*i;
        convert_help_tree_to_arr(r->left, arr, i);
    }
    if (r->right) {
        ++*i;
        convert_help_tree_to_arr(r->right, arr, i);
    }
}
