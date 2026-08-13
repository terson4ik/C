#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "other.h"

#define BUF_SIZE 4096

const char *articles[] = { /* AHTUNG!!! Strings need sorted */
    "a", "am", "and", "are", "as", "at", "do", "in", "is", "so",
    "the", "this", "to", "was", "well",  "will",
};

int main()
{
    get_word_mechanizm *getw_var = init_get_word_var(BUF_SIZE);
    word_tree *root = NULL;
    int nl = 1;

    while (get_word(getw_var) != EOF)
        if(isalpha(*(getw_var->buf)) && 
                bin_search(getw_var->buf, articles, sizeof(articles) /
                                                 sizeof(*articles)) == NULL) {
            root = word_tree_add(root, getw_var->buf, nl);
        } else if (*(getw_var->buf) == '\n')
            nl++;
    word_tree_print(root);

    word_tree_erase(root);
    remove_get_word_var(&getw_var);
    return 0;
}
