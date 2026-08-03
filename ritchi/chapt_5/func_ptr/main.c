#include <stdio.h>
#include "my_string.h"
#include "quic_sort.h"
#include "inp_out.h"

#define MAX_LINES 5000

int main(int argc, char **argv)
{
    static char *lineptr[MAX_LINES]; /* Live in .bss */
    int nlines;
    int numeric = 0; /* 1 if numbers sort */

    if (argc > 1 && my_strcmp(argv[1], "-n") == 0)
        numeric = 1;
    nlines = readlines(lineptr, MAX_LINES);
    if (nlines >= 0) {
        quic_sort((void **)lineptr, 0, nlines - 1, 
                (int (*)(void *, void *)) (numeric ? my_numcmp : my_strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        fputs("Input too big to sort\n", stderr);
        return 1;
    }
}
