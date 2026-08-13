#ifndef MY_TREE_H
#define MY_TREE_H

typedef struct tree_word_tag tree_word;

struct word_count_tag {
    char *word;
    int count;
};
typedef struct word_count_tag word_count;

tree_word *tree_word_add(tree_word *root, char *word);
int tree_word_size(tree_word *root);
void convert_tree_to_arr(tree_word *root, word_count arr[]);
void print_word_arr(word_count arr[], int size);
void tree_word_erase(tree_word *root);

#endif
