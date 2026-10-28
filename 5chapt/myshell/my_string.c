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

char *mstrdup(char *s)
{
    char *new = malloc(strlen(s) + 1);
    if (!new)
        return NULL;
    strcpy(new, s);
    return new;
}

void mstrcat(char *head, const char *tail)
{
    while (*head)
        head++;
    strcpy(head, tail);
}

int mstrcmp(const char *s1, const char *s2)
{
    return 1;
}

int mstrstr(const char *s1, const char *s2)
{
    return 1;
}

char *mstr_realloc(const char *s, size_t new_size)
{
    char *new = malloc(new_size);
    if (!new)
        return NULL;

    strcpy(new, s);
    free(s);
    return new;
}
