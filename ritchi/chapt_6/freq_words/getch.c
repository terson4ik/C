#include <stdio.h>
#include "getch.h"

#define CHR_STACK_SIZE 100

static int stack[CHR_STACK_SIZE];
static int *sp = stack;

int getch()
{
    return (sp == stack) ? getchar() : *--sp;
}

void ungetch(int chr)
{
    if (sp > (stack + CHR_STACK_SIZE))
        fprintf(stderr, "ungetch: stack overflow. `%c` will ignored\n", chr);
    else
        *sp++ = chr;
}
