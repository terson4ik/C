#include <stdio.h>
#include <ctype.h>
#include "getop.h"
#include "getch.h"
#include "check_word.h"

int get_op(char s[])
{
    int c, i; /* need `c` to catch EOF */

    s[0] = c = get_not_space();
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
        if (isalpha(c) || c == LAST_VR) { /* maybe this is a command or variable */
            c = getch();
            if (isalpha(c)) {
                s[1] = c;
                i = 1;
                while (isalpha(s[++i] = c = getch()))
                    ;
                s[i] = '\0';
                ungetch(c);
                return check_word(s);
            } else { /* after checking, it's a variable */
                ungetch(c);
                return VAR_OP;
            }
        } else
            return c;
    }
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return s[0];
        }
        s[1] = c;
    }
    i = (s[1] == '\0') ? 0 : 1;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    ungetch(c);

    return NUMBER;
}
