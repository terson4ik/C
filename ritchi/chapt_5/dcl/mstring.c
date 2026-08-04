#include "mstring.h"

char *mstrcpy(char *dst, const char *src)
{
    char *pdst = dst;
    while ((*dst++ = *src++)) { /* if \0 then stop */
    }
    return pdst;
}

char *mstrcat(char *dst, const char *tail)
{
    char *pdst = dst;
    while (*dst)
        dst++;
    while ((*dst++ = *tail++)) { /* if \0 then stop */
    }
    return pdst;
}
