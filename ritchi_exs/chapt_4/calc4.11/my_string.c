#include "my_string.h"

int cmp_str(const char *s1, const char *s2)
{
    int i = 0, j = 0;

    while (s1[i] != '\0' && to_lower(s1[i]) == to_lower(s2[j]))
        i++, j++;
    return (s1[i] == '\0' && s2[j] == '\0') ? 1 : 0;
}

int str_len(const char *s)
{
    const char *t = s;
    while(*t)
        t++;
    return t - s;
}

void reverse(char *s)
{
    int i, j;

    for (i = 0, j = str_len(s)-1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void copy_str(char *dest, const char *src)
{
    const char *s = src;
    char *d = dest;
    while ((*d++ = *s++)) /* '\0' == 0. STOP */
        ;
}

char to_upper(char c)
{
    return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
}
char to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
