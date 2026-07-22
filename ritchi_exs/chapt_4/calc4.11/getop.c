#include <stdio.h>
#include <ctype.h>
#include "getop.h"
#include "check_word.h"

int get_op(char s[])
{
    static int last_c = EOF;
    int i;
    last_c = (last_c == EOF) ? getchar() : last_c;
    while (last_c == ' ' || last_c == '\t')
        last_c = getchar();

    s[0] = last_c;
    s[1] = '\0';
    if (!isdigit(last_c) && last_c != '.' && last_c != '+' && last_c != '-') {
        if (isalpha(last_c) || last_c == LAST_VR) { 
            /* maybe this is a command or variable */
            last_c = getchar();
            if (isalpha(last_c)) {
                s[1] = last_c;
                i = 1;
                while (isalpha(s[++i] = last_c = getchar()))
                    ;
                s[i] = '\0';
                return check_word(s);
            } else { /* after checking, it's a variable */
                return VAR_OP;
            }
        } else {
            int tmp = last_c;
            last_c = EOF;
            return tmp;
        }
    }
    if (last_c == '+' || last_c == '-') {
        last_c = getchar();
        if (!isdigit(last_c) && last_c != '.') {
            return s[0];
        }
        s[1] = last_c;
    }
    i = (s[1] == '\0') ? 0 : 1;
    if (isdigit(last_c))
        while (isdigit(s[++i] = last_c = getchar()))
            ;
    if (last_c == '.')
        while (isdigit(s[++i] = last_c = getchar()))
            ;
    s[i] = '\0';
    return NUMBER;
}
