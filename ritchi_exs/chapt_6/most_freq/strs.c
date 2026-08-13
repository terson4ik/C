#include <stdlib.h>
#include <stdio.h> /* for NULL */
#include "strs.h"

int str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r - s;
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
    char *new_s = malloc(str_len(s) + 1); /* +1 '\0' */
    if (!new_s)
        return NULL;
    return str_cpy(new_s, s);
}

int str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
        s1++, s2++;
    return *s1 - *s2;
}
