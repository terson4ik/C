#include <stdio.h>
#include "getch.h"
#include "dcl.h"
#include "mstring.h"

int main()
{
    int type;
    char temp[2000];

    while (gettoken() != EOF) {
        mstrcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                mstrcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                mstrcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                mstrcpy(out, temp);
            } else
                fprintf(stderr, "invalid input at %s\n", token);
        printf("%s\n", out);
    }
    return 0;
}
