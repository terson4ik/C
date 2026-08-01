#include <stdio.h>
#include <ctype.h>
#include "custom_lib.h"

#define DEFAULT_TAB 8 /* common size to my terminal */
#define STUD_MSG "Usage: entab -4 +8| or entab 4 6 3 1 ...\n"

int main(int argc, char **argv)
{
    unsigned int tab_size, col, spaces, starts, step;
    enum modes { SEQUENCE, FIXED, UNKNOWN } mode;
    char **pargv = argv;
    int c; 

    step = starts = DEFAULT_TAB;
    mode = UNKNOWN;
    while (*++pargv) /* skip `entab` */
        if (**pargv == '-') {
            starts = strtoi(*pargv + 1);
            mode = FIXED;
        } else if (**pargv == '+') {
            step = strtoi(*pargv + 1);
            mode = FIXED;
        } else if (isdigit(**pargv)) {
            if (mode == FIXED) {
                fputs(STUD_MSG, stderr);
                return 1;
            }
            step = starts = strtoi(*pargv++);
            mode = SEQUENCE;
            break;
        } else {
            fputs(STUD_MSG, stderr);
            return 1;
        }

    tab_size = starts;
    col = spaces = 0;
    while ((c = getchar()) != EOF) {
        col++;
        if (col == (tab_size + 1)) {
            if (spaces) {
                putchar('\t');
                spaces = 0;
            }
            if (mode == SEQUENCE)
                step = (*pargv) ? strtoi(*pargv++) : step;
            else /* common mode or -4 +8 */
                col = 1; /* tab=8, col=9; print tab; 8-9=1, ALREADY first pos */
            tab_size = step;
        }

        if (c == ' ')
            spaces++;
        else { /* flush space buffer and print not space char */
            if (spaces) {
                put_n_chars(spaces, ' ');
                spaces = 0;
            }
            if (c == '\n') {
                if (mode == SEQUENCE) {
                    pargv = argv + 1; /* skip `entab` */
                    step = starts = strtoi(*pargv++);
                }
                tab_size = starts;
                col = 0;
            }
            putchar(c);
        }
    }

    if ((col % (tab_size + 1)) == 0) { /* EOF detected without '\n' */
        if (spaces)
            putchar('\t');
    } else if (spaces)
        put_n_chars(spaces, ' ');
/* if it need for next steps, type: 
    col = spaces = 0; */
    return 0;
}
