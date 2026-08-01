#include <stdio.h>
#include "custom_lib.h"

#define DEFAULT_TAB    8   /* Common size of my terminal */

int main(int argc, char **argv) 
{
    int c, column, tab_size, next_size;
    char **pargv = argv + 1;

    if (*pargv)
        tab_size = strtoi(*pargv++);
    else 
        tab_size = DEFAULT_TAB;

    if (*pargv)
        next_size = strtoi(*pargv++);
    else
        next_size = DEFAULT_TAB;

    column = 0;
    while ((c = getchar()) != EOF) {
        column++;
        if (c == '\t') {
            put_n_chars(tab_size - ((--column) % tab_size), ' ');
            column += tab_size - (column % tab_size);
            tab_size = next_size;
            next_size = (*pargv) ? strtoi(*pargv++) : next_size;
        } else {
            if (c == '\n')
                column = 0;
            putchar(c);
        }
    }
    return 0;
}
