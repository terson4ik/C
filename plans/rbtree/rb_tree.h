#ifndef RB_TREE_H
#define RB_TREE_H

typedef struct rbtree_tag rbtree;

rbtree *rbtree_add(rbtree *root, char *key, void *data);
rbtree *rbtree_min(rbtree *root);
rbtree *rbtree_max(rbtree *root);
rbtree *rbtree_search(rbtree *root, char *key);
rbtree *rbtree_right(rbtree *node);
rbtree *rbtree_left(rbtree *node);
void   *rbtree_parse_node(rbtree *node);
rbtree *rbtree_rm_key(rbtree *root, char *key);
void    rbtree_destroy(rbtree *root, int destroy_data_flag);

#endif
