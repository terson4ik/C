#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"

struct rbtree_tag {
    char *key;
    void *data;
    struct rbtree_tag *left, *right, *p;
    enum { red, black } color;
};
/* typedef must locate in a header file */

rbtree *rbtree_add(rbtree *r, char *key, void *data)
{
    if (!r) {
        if (!(r = malloc(sizeof(*r)))) /* it's smell but fast */
            return NULL;
        r->key = strdup(key);
        r->data = data;
        r->left = r->right = r->p = NULL;
        r->color = red;
    } else {
        if (r->p == NULL && r->color == red)
            r->color = black;
        int cond = strcmp(r->key, key);
        if (cond < 0) {
            r->left = rbtree_add(r->left, key, data);
            r->left->p = r;
        } else if (cond > 0) {
            r->right = rbtree_add(r->right, key, data);
            r->right->p = r;
        } /* if equal then skip */
    }
    return r;
}

rbtree *rbtree_min(rbtree *r)
{
    while (r)
        if(r->left)
            r = r->left;
        else if (r->right)
            r = r->right;
        else
            return r;
    return NULL;
}

rbtree *rbtree_max(rbtree *r)
{
    while (r)
        if (r->right)
            r = r->right;
        else if(r->left)
            r = r->left;
        else
            return r;
    return NULL;
}

rbtree *rbtree_search(rbtree *r, char *key)
{
    if (!r)
        return NULL;
    else {
        int cond = strcmp(r->key, key);
        if (cond > 0)
            return rbtree_search(r->right, key);
        else if (cond < 0)
            return rbtree_search(r->left, key);
        else
            return r;
    }
}

rbtree *rbtree_right(rbtree *nd)
{
    return nd ? nd->right : NULL;
}

rbtree *rbtree_left(rbtree *nd)
{
    return nd ? nd->left : NULL;
}

void *rbtree_parse_node(rbtree *nd)
{
    return nd ? nd->data : NULL;
}

rbtree *rbtree_rm_key(rbtree *r, char *key)
{
    return r;
}

void rbtree_destroy(rbtree *r, int destroy_data)
{
    if (!r)
        return;
    rbtree_destroy(r->left, destroy_data);
    rbtree_destroy(r->right, destroy_data);

    if (destroy_data)
        free(r->data);
    free(r->key);
    free(r);
}
