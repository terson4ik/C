#include <stdio.h>
#include "getw.h"
#include "getch.h"

#define is_space(c) ((c) == ' ' || (c) == '\n' || (c) == '\t')
#define is_alpha(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

int getword(char *buf, int lim)
{
    int c;
    char *runner = buf;

    for (c = getch(); is_space(c); c = getch())
        ;

    *runner++ = c;
    if (!is_alpha(c)) {
        runner = '\0';
        return c; /* int will be returned because EOF is int */
    }

    for (c = getch(); --lim > 0 && is_alpha(c); c = getch())
        *runner++ = c;
    *runner = '\0';
    ungetch(c);
    return *buf; /* alpha will returned */
}
