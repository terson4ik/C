#include <stdio.h> /* printf + NULL */
#include <stdlib.h> /* malloc */
#include "tree.h"
#include "strs.h"

static struct tnode *talloc(void);

struct tnode *addtree(struct tnode *p, char *word)
{
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = str_dup(word);
        p->count = 1;
        return p;
    }

    cond = str_cmp(p->word, word);
    if (cond == 0) /* equal */
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, word);
    else /* cond > 0 */
        p->right = addtree(p->right, word);

    return p;
}

void treeprint(struct tnode *r)
{
    if (!r)
        return;

    treeprint(r->left);
    printf("%4d, %s\n", r->count, r->word);
    treeprint(r->right);
}

struct tnode *erase_tree(struct tnode *r)
{
    if (!r)
        return NULL;

    if (r->left)
        r->left = erase_tree(r->left);
    if (r->right)
        r->right = erase_tree(r->right);

    /* leap */
    free(r->word);
    free(r);
    return NULL;
}

static struct tnode *talloc(void)
{
    struct tnode *item = malloc(sizeof(struct tnode));
    item->word = NULL;
    item->left = item->right = NULL;
    return item;
}
