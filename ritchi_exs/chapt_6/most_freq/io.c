#include <stdio.h>
#include <ctype.h>
#include "io.h"

int get_word(char *buf, int lim)
{
    char *runner = buf;
    int c;

    if (lim < 2)
        return EOF;
    while (isspace(c = getchar()))
        ;

    lim--;
    *runner++ = c;
    if (!isalpha(c)) {
        *runner = '\0';
        return c; /* EOF detected */
    }
    while(--lim > 0 && isalpha(c = getchar()))
        *runner++ = c;
    *runner = '\0';
    ungetc(c, stdin);
    return *buf;
}
