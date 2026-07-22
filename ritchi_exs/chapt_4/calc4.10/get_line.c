#include <stdio.h>
#include "get_line.h"

int get_line(char *s, int lim)
{
    int c, i;

    if (!lim)
        return 0;

    i = 0;
    while (--lim && (c = getchar()) != EOF) {
        s[i++] = c;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}
