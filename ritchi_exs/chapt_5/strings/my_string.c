#include "my_string.h"

/* strncpy(buf, "1", 5);       // { '1',   0,   0,   0,   0 }
   strncpy(buf, "123456", 5);  // { '1', '2', '3', '4', '5' } */
char *strncopy(char *dst, const char *src, size_t size)
{
    char *saveptr = dst;

    while (size && (*dst++ = *src++))
        size--;

    if (size)
        while (--size) /* dst-1 have 0 */
            *dst++ = '\0';
        
    return saveptr;
}

char *strncaten(char *dst, const char *src, size_t size)
{
    char *saveptr = dst;
    
    while (*dst)
        dst++;

    while (size && (*dst++ = *src++))
        size--;

    if (!size)
        *dst = '\0';

    return saveptr;
}

int   strncomp(const char *s1, const char *s2, size_t n)
{
    if (!n)
        return 0;

    while (--n && *s1 == *s2) { /* it's stop in moment s1 ??? s2 */
        if (*s1 == '\0' || *s2 == '\0')
            break;
        s1++, s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}
