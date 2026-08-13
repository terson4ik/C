#ifndef MY_TREE
#define MY_TREE

typedef struct word_tree_tag word_tree;

word_tree *word_tree_add(word_tree *root, const char *word, int line);
void word_tree_print(word_tree *root);
void word_tree_erase(word_tree *root);

#endif
