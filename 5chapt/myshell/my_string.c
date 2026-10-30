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

char *mstrstr(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;

    if (*s2 == '\0')
        return (char*)s1;

    for (; *s1; s1++) {
        const char *r1 = s1;
        const char *r2 = s2;
        for (; (*r1 && *r2) && (*r1 == *r2); r1++, r2++)
        {}

        if (*r2 == '\0')
            return (char*)s1;
    }

    return NULL;
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
