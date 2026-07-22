#include <stdio.h>
#include "getch.h"
#include "my_string.h"

static int last_ch = EOF;
static char signal_EOF = 0;
int getch()
{
    int t = last_ch;
    last_ch = EOF; /* in place change because it faster then if-else */
    if(!signal_EOF)
        return (t != EOF) ? t : getchar();
    else {
        signal_EOF = 0; /* flush to the next file descriptor */
        return EOF;
    }
}

void ungetch(int c)
{
    if (last_ch == EOF && !signal_EOF) {
        if(c == EOF)
            signal_EOF = 1;
        last_ch = c;
    } else    /* if user abuse this feature */
        fprintf(stderr, "TOO MANY CHARACTERS\n");
}

int get_not_space()
{
    int c;
    while ((c = getch()) == ' ' || c == '\t')
        ; /* isspace(c) not using because it eat '\n' */
    return c;
}

#define INP_MAX 100

static int chars[INP_MAX];
static int chr_ptr = 0;

int legacy_getch()
{
    return (chr_ptr > 0) ? chars[--chr_ptr] : getchar();
}

void legacy_ungetch(int c)
{
    if (chr_ptr >= INP_MAX)
        fprintf(stderr, "TOO MANY CHARACTERS\n");
    else
        chars[chr_ptr++] = c;
}

void ungets(char *s)
{
    int i; /* alternative: malloc, copy, reverse, and write directly to buf */
    for (i = str_len(s) - 1; i >= 0; i--)
        legacy_ungetch(s[i]);
}
