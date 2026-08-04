#include <stdio.h>
#include "getch.h"

#define CHR_STACK_SIZE 200

static int chr_stack[CHR_STACK_SIZE];
static int *chr_prt = chr_stack;

int getch()
{
    return (chr_prt <= chr_stack) ? getchar() : *--chr_prt;
}

void ungetch(int c)
{
    if (chr_prt >= chr_stack + CHR_STACK_SIZE)
        fprintf(stderr, "Stack overflow, skip char: %c\n", c);
    else
        *chr_prt++ = c;
}
