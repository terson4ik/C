#ifndef MY_TREE_H
#define MY_TREE_H

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *word);
void treeprint(struct tnode *root);
struct tnode *erase_tree(struct tnode *root);

#endif
