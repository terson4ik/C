#include <stdlib.h> /* malloc */
#include "strs.h"

unsigned int str_len(const char *s)
{
    const char *run = s;
    while (*run)
        run++;
    return run - s;
}

char *str_cpy(char *dst, const char *src)
{
    char *save = dst;
    while ((*save++ = *src++)) /* when '\0' then stop */
        ;
    return dst;
}

char *str_dup(const char *s)
{
    char *new_word = malloc(str_len(s) + 1); /* +1 for '\0' */
    if (new_word)
        str_cpy(new_word, s);
    return new_word;
}

int str_cmp(const char *s1, const char *s2)
{        /* if s1 or s2 contain \0 elem then stop */
    while ((*s1 && *s2) && (*s1 == *s2))
        s1++, s2++;
    return *s1 - *s2;
}
