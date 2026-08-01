#include <stdio.h>
#include <ctype.h>
#include "custom_lib.h"

#define DEFAULT_TAB    8   /* Common size of my terminal */
#define STUD_MSG "Usage: entab -4 +8| or entab 4 6 3 1 ...\n"

int main(int argc, char **argv) 
{
    unsigned int col, tab_size, start, step;
    char **pargv = argv;
    enum modes { SEQUENCE, FIXXED, DEFAULT } mode;
    int c;
    
    start = step = DEFAULT_TAB;
    mode = DEFAULT;
    while (*++pargv)
        if (**pargv == '-') {
            start = strtoi(*pargv + 1);
            mode = FIXXED;
        } else if (**pargv == '+') {
            start = strtoi(*pargv + 1);
            mode = FIXXED;
        } else if (isdigit(**pargv)) {
            if (mode == FIXXED) {
                fputs(STUD_MSG, stderr);
                return 1;
            }
            start = step = strtoi(*pargv);
            mode = SEQUENCE;
        } else
            fputs(STUD_MSG, stderr);

    tab_size = start;
    col = 0;
    while ((c = getchar()) != EOF) {
        col++;
        if (c == '\t') {
            int spaces;
            if (mode == FIXXED)
                tab_size = (col > (start)) ? step : start;
            else
                while (col > tab_size && *pargv)
                    tab_size = strtoi(*pargv++);

            spaces = tab_size - ((col - 1) % tab_size);
            put_n_chars(spaces, ' ');
            col += spaces - 1;
        } else {
            if (c == '\n') {
                if (mode == SEQUENCE) {
                    pargv = argv + 1;
                    tab_size = strtoi(*pargv++);
                }
                col = 0;
            }
            putchar(c);
        }
    }
    return 0;
}
