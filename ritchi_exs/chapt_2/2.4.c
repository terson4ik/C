#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 1024

char *squeeze(char *s1, const char *s2);
void str_n_copy(char *s1, const char *s2, int n);

int main(int argc, char **argv)
{
    char str[MAX_SIZE];

    if(argc < 3)
        return 0;
    
    str_n_copy(str, argv[1], MAX_SIZE);
    printf("%s\n", squeeze(str, argv[2]));
    return 0;
}

/* IS A DEMONSTRATION FUNCTION. USE LEGAL strncopy from <string.h> */
void str_n_copy(char *s1, const char *s2, int n)
{
    if(!n)
        return;
    while(n-- && (*(s1++) = *(s2++))) {
    }

    if(!n)
        *(--s1) = '\0';
}

char *squeeze(char *s1, const char *s2)
{
    int i, j;
#ifndef ECONOM 
    /* Create ASCII TABLE */
    unsigned char ascii_tab[UCHAR_MAX + 1] = {0};
    for(i = 0; s2[i] != '\0'; i++)
        ascii_tab[(unsigned int)s2[i]] = 1;
#endif
    for(i = j = 0; s1[i] != '\0'; i++) {
#ifndef ECONOM 
        if(ascii_tab[(unsigned int)s1[i]] == 0)
            s1[j++] = s1[i];
#else
        char match = 0;
        int k;
/* TODO: take out in func, BUT IN CYCLE IS TOO SLOWLY */
        for(k = 0; s2[k] != '\0'; k++)
            if(s1[i] == s2[k]) {
               match = 1;
               break;
            }
        if(!match)
            s1[j++] = s1[i];
#endif
    }
    s1[j] = '\0';
    return s1;
}
