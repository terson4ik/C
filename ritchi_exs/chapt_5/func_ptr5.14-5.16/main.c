#include <stdio.h>
#include "my_string.h"
#include "quic_sort.h"
#include "inp_out.h"

#define MAX_LINES 5000
static int set_args(const char **argv, int *numeric, enum orders *order,
                     int *forced, int *dir);

int main(int argc, char **argv)
{
    static char *lineptr[MAX_LINES]; /* Live in .bss */
    int nlines, numeric, forced, dir;

    enum orders order = DEFAULT;
    dir = forced = numeric = 0;
    if (set_args((const char **)argv, &numeric, &order, &forced, &dir) < 0)
        return 1;
    nlines = readlines(lineptr, MAX_LINES);
    if (nlines >= 0) {
        int (*comp)(void *, void *);
        if (numeric)
            comp = (int (*)(void *, void *)) my_numcmp;
        else if (dir && forced)
            comp = (int (*)(void *, void *)) dir_case_cmp;
        else if (dir)
            comp = (int (*)(void *, void *)) dir_cmp;
        else if (forced)
            comp = (int (*)(void *, void *)) my_strcasecmp;
        else
            comp = (int (*)(void *, void *)) my_strcmp;

        quic_sort((void **)lineptr, 0, nlines - 1, comp, order);
        writelines(lineptr, nlines);
        return 0;
    } else {
        fputs("Input too big to sort\n", stderr);
        return 1;
    }
}

static int set_args(const char **argv, int *numeric, enum orders *order,
     int *forced, int *dir)
{
    while ((*++argv) && **argv == '-') {
        int c = *(++(*argv));
        do  {
            switch (c)
            {
            case 'n':
                *numeric = 1;
                break;
            case 'r':
                *order = REVERSE;
                break;
            case 'f':
                *forced = 1;
                break;
            case 'd':
                *dir = 1;
                break;
            case '\0':
                fputs("Detected empty option... Abort\n", stderr);
                return -1;
            default:
                fprintf(stderr, "Unknown option: %c\n", c);
                return -1;
                break;
            }
        } while ((c = *(++(*argv))) != '\0');
    }
    return 1;
}