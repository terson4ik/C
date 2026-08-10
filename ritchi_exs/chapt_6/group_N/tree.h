#ifndef MY_TREE_H
#define MY_TREE_H

typedef struct prefix_tree_tag prefix_tree;

prefix_tree *prefix_tree_add(prefix_tree *root, char *word, const unsigned int size);
void prefix_tree_print(prefix_tree *root);
void prefix_tree_erase(prefix_tree *root);

#endif
