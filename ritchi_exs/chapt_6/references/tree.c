#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "strs.h"

struct int_list_tag {
    int i;
    struct int_list_tag *next;
};
typedef struct int_list_tag int_list;

struct int_que_tag {
    int_list *f, *l;
};
typedef struct int_que_tag int_que;

struct word_tree_tag {
    char *word;
    int_que *refs;
    struct word_tree_tag *left, *right;
};
/* type_def was declared in header as API */

static word_tree *word_tree_new();
static void que_add(int_que **qp, int i);
word_tree *word_tree_add(word_tree *r, const char *word, int ln)
{
    int cond;
    if (!r) {
        r = word_tree_new();
        que_add(&r->refs, ln);
        r->word = str_dup(word);
        return r;
    }

    cond = str_cmp(word, r->word);
    if (cond == 0)
        que_add(&r->refs, ln);
    else if(cond < 0)
        r->left = word_tree_add(r->left, word, ln);
    else /* if(cond > 0) */
        r->right = word_tree_add(r->right, word, ln);

    return r;
}

static void int_list_print(int_list *plist);
void word_tree_print(word_tree *r)
{
    if (!r)
        return;

    if (r->left)
        word_tree_print(r->left);

    printf("%s: ", r->word);
    int_list_print(r->refs->f);

    if (r->right)
        word_tree_print(r->right);
}

static void int_list_erase(int_list *f);
void word_tree_erase(word_tree *r)
{
    if (!r)
        return;

    if (r->left)
        word_tree_erase(r->left);
    if (r->right)
        word_tree_erase(r->right);

    free(r->word);
    int_list_erase(r->refs->f);
    free(r->refs);
    free(r);
}
/* private functions */
static word_tree *word_tree_new()
{
    word_tree *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    new->refs = malloc(sizeof(int_que));
    if (!new->refs)
        return NULL;
    new->refs->f = new->refs->l = NULL;
    new->word = NULL;
    new->left = new->right = NULL;
    return new;
}

static void que_add(int_que **qp, int i)
{
    int_list *new = malloc(sizeof(int_list));
    if (!new)
        return; /* error */

    new->i = i;
    new->next = NULL;

    if ((*qp)->f) {
        (*qp)->l->next = new;
        (*qp)->l = (*qp)->l->next;
    } else
        (*qp)->f = (*qp)->l = new;
}

static void int_list_print(int_list *plist) /* its just a address */
{
    while (plist) {
        printf("%d%s", plist->i, (plist->next) ? ", " : "\n");
        plist = plist->next;
    }
}

static void int_list_erase(int_list *f)
{
    while (f) {
        int_list *cur = f;
        f = f->next;
        free(cur);
    }
}
