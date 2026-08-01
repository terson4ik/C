#include <stdio.h>
#include "custom_lib.c"

#define DEFAULT_TAB 8 /* common size to my terminal */

int main(int argc, char **argv)
{
    int c, column, spaces, tab_size, next_size; 
    char **pargv = argv;
    pargv++;
    if (*pargv == NULL)
        next_size = tab_size = DEFAULT_TAB;
    else {
        tab_size = strtoi(*pargv++);
        if (*pargv != NULL)
            next_size = strtoi(*pargv++);
        else
            next_size = DEFAULT_TAB;
    }
    spaces = column = 0;
    while ((c = getchar()) != EOF) {
        column++;
        if ((column % (tab_size + 1)) == 0) {
            if (spaces)
                putchar('\t');
            tab_size = next_size;
            if (*pargv != NULL)
                next_size = strtoi(*pargv++);
            spaces = 0;
        }
        if (c == ' ')
            spaces++;
        else {
            if (c == '\n')
                column = 0;
            put_n_chars(spaces, ' ');
            spaces = 0;
            putchar(c);
        }
    }
    column++; /* Unexpected EOF */
    if (column == tab_size + 1) {
        if (spaces)
            putchar('\t');
    } else
        put_n_chars(spaces, ' ');

    return 0;
}
