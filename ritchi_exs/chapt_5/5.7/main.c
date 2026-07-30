#include <stdio.h>
#include "iovector.h"

#define MAXLINES 5000
static char *lineptr[MAXLINES];
#define MAX_ALOC_SIZE 10000
static char alloc_buf[MAX_ALOC_SIZE];
int main()
{
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES, alloc_buf, MAX_ALOC_SIZE)) 
                                                                     >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        fputs("error: input too big to sort\n", stderr);
        return 1;
    }
}
