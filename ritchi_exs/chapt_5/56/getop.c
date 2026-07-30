#include <ctype.h>
#include <stdio.h>
#include "getop.h"

static int getch(void);
static void ungetch(int c);

int getop (char *line)
{
    int c;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (!isdigit(c))
        return c;
    for (; isdigit(c); c = getch()) 
        *line++ = c;
    *line = '\0';
    ungetch(c);
    return NUMBER;
}

#define VALSIZE 100
static int val[VALSIZE];
static int *pv = val;

static int getch(void)
{
    return (pv == val) ? getchar() : *--pv;
}
static void ungetch(int c)
{
    if (pv > val + VALSIZE)
        fputs("ungetch: buffer overflow.\n", stderr);
    else
        *pv++ = c;
}
