#include "stdlib.h"
#include "my_string.h"


int my_numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
        s1++, s2++;
    return *s1 - *s2;
}

void my_str_cpy(char *dst, const char *src) 
{
    while ((*dst++ = *src++)) { /* If zero meet == break */
    }
}