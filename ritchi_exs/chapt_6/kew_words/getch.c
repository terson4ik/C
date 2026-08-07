#include <stdio.h>
#include "getch.h"

#define MAXBUF 100

static int chr_buf[MAXBUF];
static int *chr_ptr = chr_buf;

int getch()
{
    return (chr_ptr > chr_buf) ? *--chr_ptr : getchar();
}

void ungetch(int c)
{
    if (chr_ptr > chr_buf + MAXBUF)
        fprintf(stderr, "STACK FULL. ignore next char: %c\n", c);
    else
        *chr_ptr++ = c;
}
