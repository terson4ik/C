#include <stdlib.h>
#include "my_string.h"

size_t mstrlen(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r-s;
}

void mstrcpy(char *dst, const char *src)
{
    while ((*(dst++) = *(src++)))
    {}
}

char *mstrdup(const char *s)
{
    char *new = malloc(mstrlen(s) + 1);
    if (!new)
        return NULL;
    mstrcpy(new, s);
    return new;
}

void mstrcat(char *head, const char *tail)
{
    while (*head)
        head++;
    mstrcpy(head, tail);
}

int mstrcmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return (unsigned int)*s1 - (unsigned int)*s2;
}

int mstrstr(const char *s1, const char *s2)
{
    return 1;
}

char *mstr_realloc(char *s, size_t new_size)
{
    char *new = malloc(new_size);
    if (!new)
        return NULL;

    mstrcpy(new, s);
    free(s);
    return new;
}
