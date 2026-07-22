#include <stdio.h>
#include <ctype.h>
#include "getop.h"
#include "get_line.h"
#include "check_word.h"

#define MAX_LINE 1000

int get_op(char s[])
{
    static char line[MAX_LINE];
    static int size = 0;
    int i, c;
    if(size == 0 || line[size] == '\0') {
        size = 0;
        if(!get_line(line, MAX_LINE))
            return EOF;
    }
    while (line[size] != '\0' && (line[size] == ' ' || line[size] == '\t'))
        size++;
    s[0] = c = line[size];
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
        if (isalpha(c) || c == LAST_VR) { /* maybe this is a command or variable */
            if (line[++size] != '\0' && isalpha(line[size])) {
                s[1] = line[size];
                i = 1;
                while (line[++size] != '\0' && isalpha(s[++i] = line[size]))
                    ;
                s[i] = '\0';
                return check_word(s);
            } else { /* after checking, it's a variable */
                return VAR_OP;
            }
        } else {
            size++;
            return c;
        }
    }
    if (c == '+' || c == '-') {
        if (line[++size] != '\0' && !isdigit(line[size]) && line[size] != '.') {
            return s[0];
        }
        s[1] = line[size];
    }
    i = (s[1] == '\0') ? 0 : 1;
    if (isdigit(line[size]))
        while (line[++size] != '\0' && isdigit(s[++i] = line[size]))
            ;
    if (line[size] == '.')
        while (line[++size] != '\0' && isdigit(s[++i] = line[size]))
            ;
    s[i] = '\0';
    return NUMBER;
}
