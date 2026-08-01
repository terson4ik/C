#include <stdio.h>

int get_line (char *str, int lim)
{
    int c;
    char *run = str;
    while (--lim > 0 && (c = getchar()) != EOF) {
        *run++ = c;
        if (c == '\n')
            break;
    }
    *run = '\0';
    return run - str;
}

char *str_str(const char *s1, const char *s2)
{
    const char *r1;

    for (r1 = s1; *r1; r1++) {
        const char *tmpr1 = r1;
        const char *r2 = s2;
        while (*r2 != '\0' && *r2 == *tmpr1)
            r2++, tmpr1++;
        if (*r2 == '\0')
            return (char *)r1;
    }
    return NULL;
}
