#include <stdio.h>
#include "std_lib.h"

int main() /* int argc, char **argv */
{
    char *p;
    p = alloc(4);
    *(p) = 'h';
    *(p+1) = 'i';
    *(p+2) = '\n';
    *(p+3) = '\0';
    printf("%s", p);

    afree(p);
    return 0;
}
