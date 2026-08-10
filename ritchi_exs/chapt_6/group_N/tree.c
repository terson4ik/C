#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "strs.h"

struct word_tree_tag {
    char *word;
    struct word_tree_tag *left;
    struct word_tree_tag *right;
};
typedef struct word_tree_tag word_tree;

struct prefix_tree_tag {
    char *prefix;
    word_tree *words;
    struct prefix_tree_tag *left;
    struct prefix_tree_tag *right;
};
/* typedef prefix tree will used in header file (public API) */

static prefix_tree *new_prefix_node();
static word_tree *word_tree_add(word_tree *r, char *word);

prefix_tree *prefix_tree_add(prefix_tree *r, char *word, const unsigned int size)
{
    char cond;
    if (str_len(word) < size)
        return r;

    if (!r) {
        r = new_prefix_node();
        r->prefix = str_n_dup(word, size);
        r->words = word_tree_add(r->words, word);
        return r;
    }
    cond = str_n_cmp(word, r->prefix, size);
    if (cond == 0) /* most frequency condition */
        r->words = word_tree_add(r->words, word);
    else if (cond > 0)
        r->right = prefix_tree_add(r->right, word, size);
    else /* if (cond < 0); automatic go to */
        r->left = prefix_tree_add(r->left, word, size);

    return r;
}

static void word_tree_print(word_tree *r);

void prefix_tree_print(prefix_tree *r)
{
    if (!r)
        return;

    if (r->left)
        prefix_tree_print(r->left);
    printf("Group:%s\n", r->prefix);
    word_tree_print(r->words);
    if (r->right)
        prefix_tree_print(r->right);

}

static void word_tree_erase(word_tree *r);

void prefix_tree_erase(prefix_tree *r)
{
    if (!r)
        return;

    if (r->left)
        prefix_tree_erase(r->left);
    if (r->right)
        prefix_tree_erase(r->right);
    word_tree_erase(r->words);
    free(r->prefix);
    free(r);
}

static void word_tree_erase(word_tree *r)
{
    if (!r)
        return;

    if (r->left)
        word_tree_erase(r->left);
    if (r->right)
        word_tree_erase(r->right);
    free(r->word);
    free(r);
}

static void word_tree_print(word_tree *r)
{
    if (!r)
        return;

    if (r->left)
        word_tree_print(r->left);
    printf("%s\n", r->word);
    if (r->right)
        word_tree_print(r->right);

}

static prefix_tree *new_prefix_node()
{
    prefix_tree *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    new->words = NULL;
    new->prefix = NULL;
    new->left = new->right = NULL;
    return new;
}

static word_tree *new_word_node();

static word_tree *word_tree_add(word_tree *r, char *word)
{
    int cond;
    if (!r) {
        r = new_word_node();
        r->word = str_dup(word);
        return r;
    }
    cond = str_cmp(word, r->word);
    if (cond < 0)
        r->left = word_tree_add(r->left, word);
    else if (cond > 0)
        r->right = word_tree_add(r->right, word);
    /* if cond == 0 then skip, counter not needed */
    return r;
}

static word_tree *new_word_node()
{
    word_tree *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    new->word = NULL;
    new->left = new->right = NULL;
    return new;
}
