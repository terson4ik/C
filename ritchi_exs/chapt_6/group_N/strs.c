#include <stdlib.h> /* malloc */
#include "strs.h"

unsigned int str_len(const char *s)
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

char *str_n_cpy(char *dst, const char *src, int n)
{
    char *r = dst;
    while (--n >= 0 && (*r++ = *src++))
        ;
    while (--n >= 0)
        *r++ = '\0';
    return dst;
}

char *str_dup(const char *s)
{
    char *new_str = malloc(str_len(s) + 1); /* +1 for '\0' */
    str_cpy(new_str, s);
    return new_str;
}

char *str_n_dup(const char *s, int n)
{
    char *new_w = malloc(n + 1); /* + '\0' */
    str_n_cpy(new_w, s, n);
    new_w[n] = '\0';
    return new_w;
}

int str_cmp(const char *s1, const char *s2)
{
    while ((*s1 && *s2) && (*s1 == *s2))
        s1++, s2++;
    return (unsigned char) *s1 - (unsigned char) *s2;
}

int str_n_cmp(const char *s1, const char *s2, int n)
{
    while (--n > 0 && (*s1 && *s2) && (*s1 == *s2))
        s1++, s2++;
    return (unsigned char) *s1 - (unsigned char) *s2;
}
