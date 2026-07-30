#include <stdio.h>
#include "get_line.h"

int get_line(char *s, int lim)
{
    char *runner = s;
    int c;
    while (--lim > 0 && (c = getchar()) != EOF) {
        *runner++ = c;
        if (c == '\n')
            break;
    }
    *runner = '\0';

    return runner - s;
}
