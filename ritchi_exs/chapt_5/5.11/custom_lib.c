#include <stdio.h>
#include "custom_lib.h"
#define ISNUM(x) (((x) >= '0' && (x) <= '9') ? 1 : 0)

void put_n_chars(int n, char c)
{
    while ((n)-- > 0)
        putchar(c);
}

int strtoi(const char *s)
{
    int res, sign = 1;
    if (!ISNUM(*s) && (*s == '-' || *s == '+'))
        sign = (*s++ == '-') ? -1 : 1;
    for (res = 0; ISNUM(*s); s++)
        res = res * 10 + *s - '0';
    return res * sign;
}
