#include <stdio.h>
#include "getch.h"

#define INP_MAX 100

static int chars[INP_MAX];
static int chr_ptr = 0;

int getch()
{
    return (chr_ptr > 0) ? chars[--chr_ptr] : getchar();
}

int get_not_space()
{
    int c;
    while ((c = getch()) == ' ' || c == '\t')
        ; /* isspace(c) not using because it eat '\n' */
    return c;
}
void ungetch(int c)
{
    if (chr_ptr >= INP_MAX)
        fprintf(stderr, "TOO MANY CHARACTERS\n");
    else
        chars[chr_ptr++] = c;
}
