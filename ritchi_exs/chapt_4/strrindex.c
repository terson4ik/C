#include <stdio.h>

int strrindex(char source[], char search[]);
int str_size(const char s[]);

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    printf("%d\n", strrindex(argv[1], argv[2]));
    return 0;
}

int strrindex(char s[], char t[])
{
    int i, j;

    for (i=str_size(s)-str_size(t); i >= 0; i--) {
        int k;
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if(t[k] == '\0')
            return i;
    }
    
    return -1;
}

int str_size(const char s[])
{
    const char *t = s;
    while (*t++ != '\0') {
    }

    return t - 1 - s ;
}
