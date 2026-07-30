#include "mstring.h"

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2) {
        if (*s1 == '\0' || *s2 == '\0')
            break;
        s1++, s2++;
    }
    return *s1 - *s2;
}

int my_strlen(const char *s)
{
    const char *tmp = s;
    while (*tmp)
        tmp++;
    return tmp - s;
}

char *my_strcpy(char *dst, const char *src)
{
    char *saveptr = dst;
    
    while ((*dst++ = *src++)) /* in '\0' then exit */
        ;

    return saveptr;
}
