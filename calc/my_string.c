#include "my_string.h"

int cmp_str(const char *s1, const char *s2)
{
    int i = 0, j = 0;

    while (s1[i] != '\0' && to_lower(s1[i]) == to_lower(s2[j]))
        i++, j++;
    return (s1[i] == '\0' && s2[j] == '\0') ? 1 : 0;
}

char to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
