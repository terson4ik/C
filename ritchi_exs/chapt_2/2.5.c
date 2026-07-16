#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 1024

#ifdef STD_C
char *any(char *s1, const char *s2);
#else
int any(char *s1, const char *s2);
#endif

char *copy_n(char *s1, const char *s2, unsigned int n);
int main(int argc, char **argv)
{
    char str[MAX_SIZE];

    if(argc < 3)
        return 0;

#ifdef STD_C
    printf("%s\n", any(copy_n(str, argv[1], MAX_SIZE), argv[2]));
#else
    printf("%d\n", any(copy_n(str, argv[1], MAX_SIZE), argv[2]));
#endif
    return 0;
}

char *copy_n(char *s1, const char *s2, unsigned int n)
{
    char *tmp = s1;
    if(!n)
        return NULL;
    while(n-- && (*(s1++) = *(s2++))) {
    }
    if(!n)
        *(--s1) = '\0';

    return tmp;
}

#ifdef STD_C
char *any(char *s1, const char *s2)
#else
int any(char *s1, const char *s2)
#endif
{
    int i;
#ifndef ECONOM
    unsigned char ascii_t[UCHAR_MAX + 1] = { 0 };
    for(i = 0; s2[i]; i++)
        ascii_t[(unsigned int)s2[i]] = 1;
#endif
    for(i = 0; s1[i] != '\0'; i++) {
#ifndef ECONOM
        if(ascii_t[(unsigned int)s1[i]] != 0)
#  ifdef STD_C
            return s1 + i;
#  else
            return i + 1; /* +1 for human understandable view */
#  endif
#else
        int j;
        for(j = 0; s2[j] != '\0'; j++)
            if(s1[i] == s2[j])
#  ifdef STD_C
                return s1 + i;
#  else
                return i + 1; /* +1 for human understandable view */
#  endif
#endif
    }
#ifdef STD_C
    return NULL;
#else
    return -1;
#endif
}
