/* rainbow square */
#include <stdio.h> /* Print error messages */
#include <stdlib.h> /* exit() */
#include <curses.h>

#define SQR_SIZE    5
#define CHR_SQR     '*'
#define CHR_EMPTY   ' '
#define KEY_ESCAPE  27
#define KEY_SPACE   ' '
#define TARG_PAIR   1
#define COUNT_COLOR 8

typedef struct {
    struct point {
        int x, y;
    } up_left, down_right;
} rectangle;

void make_rect(const rectangle *r, int targ_pair);
void change_color(int targ_pair, int fg, int bg);
void handle_resize(int *row, int *col, rectangle *sqr);


int main()
{
    int row, col, key, fg, bg;
    rectangle sqr;
    fg = 0; /* white */
    bg = 7; /* black */
    const int colors[COUNT_COLOR] = {
        COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, 
        COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_BLACK
    };
    if (colors[0] != COLOR_WHITE || colors[7] != COLOR_BLACK) {
        endwin();
        fputs("DON'T TOUCH CONSTANTS IN ARRAY 'colors', look IF condition"
                "to correct set\n", stderr);
        return 200;
    }

    initscr();
    start_color();
    curs_set(0);
    if (!has_colors()) {
        endwin();
        fputs("This terminal nonsupporting color mode\n", stderr);
        return 1;
    }
    noecho();
    keypad(stdscr, 1);
    timeout(-1); /* enable block mode */

    handle_resize(&row, &col, &sqr);

    change_color(TARG_PAIR, colors[fg], colors[bg]);
    make_rect(&sqr, TARG_PAIR);

    while ((key = getch()) != KEY_ESCAPE && key != KEY_SPACE) {
        switch (key) {
        case KEY_LEFT:
            bg = (bg-1+COUNT_COLOR) % COUNT_COLOR;
            break;
        case KEY_RIGHT:
            bg = (bg+1) % COUNT_COLOR;
            break;
        case KEY_UP:
            fg = (fg+1) % COUNT_COLOR;
            break;
        case KEY_DOWN:
            fg = (fg-1+COUNT_COLOR) % COUNT_COLOR;
            break;
        case KEY_RESIZE:
            handle_resize(&row, &col, &sqr);
            clear();
            make_rect(&sqr, TARG_PAIR);
            continue;
            break;
        }
        change_color(TARG_PAIR, colors[fg], colors[bg]);
        refresh();
    }
    endwin();
    return 0;
}

void make_rect(const rectangle *r, int targ_pair)
{
    int x, y;

    attrset(COLOR_PAIR(targ_pair));
    for (x = r->up_left.x; x <= r->down_right.x; x++)
        for (y = r->up_left.y; y <= r->down_right.y; y++)
            mvaddch(y, x, CHR_SQR);

    refresh();
}

void change_color(int targ_pair, int fg, int bg)
{
    init_pair(targ_pair, fg, bg);
}

void handle_resize(int *row, int *col, rectangle *sqr)
{
    getmaxyx(stdscr, *row, *col);
    if (*row < SQR_SIZE || *col < SQR_SIZE) {
        endwin();
        fprintf(stderr, "Screen too small. %d+ need", SQR_SIZE);
        exit(1);
    }
    sqr->up_left.x = (*col-SQR_SIZE) / 2;
    sqr->up_left.y = (*row-SQR_SIZE) / 2;
    sqr->down_right.x = sqr->up_left.x + SQR_SIZE - 1;
    sqr->down_right.y = sqr->up_left.y + SQR_SIZE - 1;
}
