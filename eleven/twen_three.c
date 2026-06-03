/* this program print count off words in CMD arguments */
#include <stdio.h>

#define IN  1   /* in of the word */
#define OUT 0   /* out----------- */ 

int is_space(char c) 
{
    return c == ' ' || c == '\n' || c == '\t';
}

int count_words_stdI(const char *str) {
    const char *temp;
    int nw, state, c;
    
    state = OUT;
    for(nw = 0, temp = str; *temp; ++temp) {
        c = *temp;
        if(state == OUT && !is_space(c)) {
            ++nw;
            state = IN;
        } else if(state == IN && is_space(c)) {
            state = OUT;
        }
    }
    return nw;
}
int main(int argc, char **argv)
{
    if(argc != 2) {
        fprintf(stderr, "example of use: %s \"some words ...\"\n", argv[0]);
        return 1;
    }
    printf("%d\n", count_words_stdI(argv[1]));
    
    return 0;
}
