#include <stdio.h>
#include "my_string.h"

void print_tr_fal(int expr)
{
    printf("%d\n", expr);
}

#define GOODSIZE 150
int main() /* int argc, char **argv */
{
    char word1[GOODSIZE] = "it's my life";
    char word2[GOODSIZE] = "it's my moon";
    char word3[GOODSIZE] = " what's+leap....\n";
    char word4[GOODSIZE] = "it's my zoon";
    char word5[GOODSIZE] = "it's my ahon";
    print_tr_fal(strncomp(word1, word2, 8));
    print_tr_fal(strncomp(word1, word2, 9));
    print_tr_fal(strncomp(word1, word2, GOODSIZE));
    print_tr_fal(strncomp(word1, word4, GOODSIZE));
    print_tr_fal(strncomp(word1, word5, GOODSIZE));
    printf("%s\n", word1);
    printf("%s\n", strncopy(word1, word3, 7));
    printf("%s\n", word2);
    printf("%s\n", strncopy(word1, word2, GOODSIZE));
    puts("--------------------");
    printf("%s\n", word2);
    printf("%s\n", strncaten(word2, word1, 6));
    printf("%s\n", strncaten(word2, word2, 12));
    return 0;
}
