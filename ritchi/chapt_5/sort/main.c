#include <stdio.h>
#include "iovector.h"

#define MAXLINES 5000
static char *lineptr[MAXLINES];

int main()
{
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        fputs("error: input too big to sort\n", stderr);
        return 1;
    }
}
