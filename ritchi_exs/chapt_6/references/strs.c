#include <stdlib.h>
#include "strs.h"

unsigned int str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r - s;
}

int str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
        s1++, s2++;
    return *s1 - *s2;
}

char *str_cpy(char *dst, const char *src)
{
    char *r = dst;
    while ((*r++ = *src++))
        ;
    return dst;
}

char *str_dup(const char *s)
{
    char *new = malloc(str_len(s) + 1); /* + '\0' */
    str_cpy(new, s);
    return new;
}
