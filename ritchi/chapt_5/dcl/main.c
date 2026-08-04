#include <stdio.h>
#include "dcl.h"
#include "mstring.h"

int main()
{
    while (gettoken() != EOF) {
        mstrcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            fprintf(stderr, "syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
