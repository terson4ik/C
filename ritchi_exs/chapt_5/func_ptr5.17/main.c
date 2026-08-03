#include <stdio.h>
#include <stdlib.h> /* itoa*/
#include <ctype.h> /* For parsing the arguments*/
#include "my_string.h"
#include "quick_sort.h"
#include "inp_out.h"

#define MAX_LINES 5000
static int set_args(const char **argv, int *numeric, enum orders *order,
                     int *forced, int *dir, int *column, char ***last_k);

int main(int argc, char **argv)
{
    static char *lineptr[MAX_LINES]; /* Live in .bss */
    int nlines, numeric, forced, dir, column;
    enum orders order;
    char **last_k;

    if (set_args((const char **)argv, &numeric, &order, &forced, &dir, &column, &last_k) < 0)
        return 1;
    nlines = readlines(lineptr, MAX_LINES);
    
    if (nlines >= 0) {
        int is_k;
        do {
            int (*comp)(void *, void *);
            is_k = last_k ? 1 : 0;
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
            if (column) {
                quick_sort_word((void **)lineptr, 0, nlines - 1, comp, order, column);
                if (last_k) {
                    set_args((const char **)last_k, &numeric, &order, &forced, &dir, &column, &last_k);
                }
            } else
                quick_sort((void **)lineptr, 0, nlines - 1, comp, order);
        } while (is_k);
        
        writelines(lineptr, nlines);
        return 0;
    } else {
        fputs("Input too big to sort\n", stderr);
        return 1;
    }
}

static int set_args(const char **argv, int *numeric, enum orders *order,
     int *forced, int *dir, int *column, char ***last_k)
{
    *column = *dir = *forced = *numeric = 0;
    *order = DEFAULT;
    *last_k = NULL;
    while ((*++argv) && **argv == '-') {
        const char *cur_str = *argv;
        int c = *(++cur_str);
        do  {
            switch (c)
            {
            case 'k':
                if (*column) {
                    *last_k = (char **)argv - 1;
                    goto quit;
                }

                if (*(cur_str+1) != '\0')
                    *column = atoi(++cur_str);
                else if ((*++argv) && isdigit(**argv))
                    *column = atoi(*argv);
                else
                    return -1;
                break;
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
        } while ((c = *(++cur_str)) != '\0');
    }
quit:
    return 1;
}