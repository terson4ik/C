#include <stdio.h>
#include "other.h"

#define ERR_VALL -1
#define EMPTY 0

static int check_uniq_seq(int c);
static int skip_spaces(int c);
static void skip_macro_line();
static void skip_comments();
static void skip_quoits();

static int last_c = EMPTY;

int getword(char *buf, int lim)
{
    int c = (last_c == EMPTY) ? getchar() : last_c;
    char *w = buf;

    c = check_uniq_seq(c);
    *w++ = c;
    if (!is_alpha(c)) {
        *w = '\0';
        last_c = EMPTY;
        return c; /* EOF check */
    }

    for (c = getchar(); --lim > 0 && is_alnum(c); c = getchar())
        *w++ = c;
    *w = '\0';
    last_c = c;
    return *buf;
}

int strtoi(const char *s)
{
    int res;
    for (res = 0; *s && is_digit(*s); s++)
        res = res * 10 + *s - '0';
    return (*s == '\0') ? res : ERR_VALL;
}

static int check_uniq_seq(int c)
{
    char need_rep = 1;
    while (need_rep) {
        c = skip_spaces(c);
        switch (c) {
            case '#':
                skip_macro_line();
                break;
            case '\"':
                skip_quoits();
                break;
            case '/':
                c = getchar();
                if (c != '*') {
                    last_c = c;
                    return '/';
                }
                skip_comments();
                break;
            default:
                need_rep = 0;
                break;
        }
        if (need_rep)
            c = getchar();
    }
    return c;
}
static int skip_spaces(int c)
{
    while (is_space(c))
        c = getchar();
    return c;
}

static void skip_macro_line()
{
    int c;
    while ((c = getchar()) != EOF)
        if (c == '\\')
            continue;
        else if (c == '\n')
            break;
}

static void skip_comments()
{
    int c, last = 0;

    while ((c = getchar()) != EOF)
        if (c == '/' && last == '*')
            return;
        else
            last = c;
}

static void skip_quoits()
{
    int c;
    while ((c = getchar()) != EOF && c != '\"')
        ;
}
