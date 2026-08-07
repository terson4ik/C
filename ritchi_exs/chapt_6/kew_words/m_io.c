#include <stdio.h>
#include <ctype.h>
#include "m_io.h"
#include "getch.h"

static int skip_empty_chr();
static void skip_line();
static void skip_comment();

int getword(char *word, int lim)
{

    char *w = word;
    char is_spec_chr = 1;
    int c = skip_empty_chr();
    while (is_spec_chr) {
        switch (c) {
            case '/': /* coms */
                c = getch();
                if(c == '*') {
                    skip_comment();
                    c = skip_empty_chr();
                } else { /* no, it's div */
                    ungetch(c);
                    *w++ = '/';
                    *w = '\0';
                    return word[0];
                }
                break;
            case '\"': /* strings */
                while ((c = getch()) != '\"' && c != EOF) {
                }
                c = skip_empty_chr();
                break;
            case '#': /* macroses */
                skip_line();
                c = skip_empty_chr();
                break;
            default:
                is_spec_chr = 0;
                break;
        }
    }
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    for ( ; --lim >= 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}


static void skip_line()
{
    int c;

    while ((c = getch()) != '\n' && c != EOF)
        if (c == '\\')
            getch(); /* use in macroses */
}

static void skip_comment()
{
    int prev, next;

    prev = getch();
    while ((next = getch()) != EOF)
        if (prev == '*' && next == '/')
            break;
        else
            prev = next;
}

static int skip_empty_chr()
{
    int c;
    while (isspace(c = getch()))
        ;
    return c;
}
