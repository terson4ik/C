/* Emulation menu */
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define KEY_ESCAPE  27

#ifdef KEY_ENTER /* In Debian13, if pressed ENTER getch() return 10 or '\n' */
#  undef KEY_ENTER
#  define KEY_ENTER '\n'
#else
#  define KEY_ENTER '\n'
#endif

#define DEFAULT_BG  0
#define WHITE_BG    1
#define ERROR_CODE  200

typedef struct {
    int x, y;
    int option;
} point;

point print_args(char **strv, int start, int argc, int row, int col, int max_len);
void change_opt(point *cur, int shift, int argc, char **strv, int row,
                                                        int col,  int max_len);
unsigned int find_largest_str(char **strv);
unsigned int str_len(const char *s);

int main(int argc, char **argv)
{
    int row, col, key, largest_str;
    point curp;

    /* ./program skip */
    argc--;
    argv++;
    if (argc < 2 || argc > 100) {
        fprintf(stderr, "I need > 2 and < 100 arguments."
                " You entered %d args\n", argc);
        return ERROR_CODE;
    }

    initscr();
    start_color();
    /* Using default black-white colors then skip check has_colors() */
    init_pair(WHITE_BG, COLOR_BLACK, COLOR_WHITE);
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    cbreak();
    timeout(-1);

    getmaxyx(stdscr, row, col);
    largest_str = find_largest_str(argv);
    curp = print_args(argv, 0, argc, row, col, largest_str);
    change_opt(&curp, 0, argc, argv, row, col, largest_str);
    while ((key = getch()) != KEY_ESCAPE) {
        switch (key) {
        case KEY_UP:
            change_opt(&curp, -1, argc, argv, row, col, largest_str);
            break;

        case KEY_DOWN:
            change_opt(&curp, +1, argc, argv, row, col, largest_str);
            break;

        case KEY_ENTER:
            endwin();
            return curp.option;
            /* No break here */

        case KEY_RESIZE: /* Resize not testing */
            getmaxyx(stdscr, row, col);
            if (curp.y < row)
                curp = print_args(argv, 0, argc, row, col, largest_str);
            else
                curp = print_args(argv, curp.y-1, argc, row, col, largest_str);
            
            change_opt(&curp, 0, argc, argv, row, col, largest_str);
            break;
        }
    }

    endwin();
    return 0; /* Escape pressed */
}

void change_opt(point *cur, int shift, int argc, char **strv, int row,
                int col, int max_len)
{
    int x, y;
    if (shift == 0) {
        attrset(COLOR_PAIR(WHITE_BG));
        x = cur->x, y = cur->y; 
        mvprintw(y, x, "%.*s", col - x, strv[cur->option-1]);

    } else {
        if (cur->option+shift > argc || cur->option+shift < 1)
            return;

        if (cur->y+shift >= row || cur->y+shift < 0) {
            int start_punct;
            cur->option += shift;
            start_punct = (cur->y+shift >= row ) ? cur->option - row
                                                      : cur->option;
            print_args(strv, start_punct, argc, row, col, max_len);
        } else {
            x = cur->x, y = cur->y;
            attrset(COLOR_PAIR(DEFAULT_BG));
            mvprintw(y, x, "%.*s", col - x, strv[cur->option-1]);
            cur->y += shift;
            cur->option += shift;
        }

        x = cur->x, y = cur->y;
        attrset(COLOR_PAIR(WHITE_BG));
        mvprintw(y, x, "%.*s", col - x, strv[cur->option-1]);
    }
    refresh();
}

point print_args(char **strv, int start, int argc, int row, int col, int max_len)
{
    const int x = (max_len > col-1) ? 0 : (col-max_len-1) / 2;
    int y = (argc < row) ? (row-argc)/2 : 0;
    point up_left;
    up_left.x = x;
    up_left.y = y;
    up_left.option = start+1;

    clear();
    attrset(COLOR_PAIR(DEFAULT_BG));
    for (argc -= start, strv += start; argc > 0 && y < row; y++, argc--, strv++)
        mvprintw(y, x, "%.*s", col - x, *strv);
    attroff(COLOR_PAIR(DEFAULT_BG));
    refresh();

    return up_left;
}

unsigned int find_largest_str(char **strv)
{
    unsigned int max; 
    if (!strv) /* NULL */
        return 0;

    for (max = 0; *strv; strv++) {
        unsigned int len = str_len(*strv);
        if (max < len)
            max = len;
    }

    return max;
}

unsigned int str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r - s;
}
