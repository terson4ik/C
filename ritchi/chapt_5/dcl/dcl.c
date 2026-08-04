#include <stdio.h>
#include <ctype.h>
#include "dcl.h"
#include "mstring.h"
#include "getch.h" /* for gettoken */

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        mstrcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            fputs("error: missing )\n", stderr);
    } else if (tokentype == NAME)
        mstrcpy(name, token);
    else 
        fputs("error: expected name of (dcl)\n", stderr);
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            mstrcat(out, " function returning");    
        else {
            mstrcat(out, " array");
            mstrcat(out, token);
            mstrcat(out, " of");
        }
    }
}

int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            mstrcpy(token, "()");
            return (tokentype = PARENS);
        } else {
            ungetch(c);
            return (tokentype = '(');
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return (tokentype = BRACKETS);
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return (tokentype = NAME);
    } else
        return (tokentype = c);
}
