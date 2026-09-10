/* draw square and arrows can change rectangle size */
#include <stdio.h> /* Print error message */
#include <stdlib.h> /* exit() */
#include <curses.h>

#define SIZE_SQR    3
#define KEY_ESCAPE  27
#define KEY_SPACE   ' '
#define CHR_RECT    '*'
#define CHR_EMPTY   ' '


typedef struct {
    struct point {
        int x, y;
    } up_left, down_right;
} rectangle;

enum sides { horizontal, vertical };

void print_full_rect(const rectangle *rect);
void handle_resize(int *row, int *col, rectangle *rect);
void print_new_sides(const rectangle *rect, enum sides side, int chr);

int main()
{
    int row, col, key;
    rectangle rect;
    
    initscr();
    curs_set(0);
    keypad(stdscr, 1);
    noecho();
    timeout(-1); /* guaranteed block */

    getmaxyx(stdscr, row, col);
    if (row < SIZE_SQR+2 || col < SIZE_SQR+2) {
        endwin();
        fprintf(stderr, "Screen size must be greater that %d.\n", SIZE_SQR);
        return 1;
    }

    rect.up_left.x    = (col - SIZE_SQR) / 2;
    rect.up_left.y    = (row - SIZE_SQR) / 2;
    rect.down_right.x = rect.up_left.x + SIZE_SQR - 1;
    rect.down_right.y = rect.up_left.y + SIZE_SQR - 1;
    print_full_rect(&rect);

    while ((key = getch()) != KEY_ESCAPE && key != KEY_SPACE) {
        switch (key) {
        case KEY_RIGHT:
            if (rect.up_left.x > 0 && rect.down_right.x < col - 1) {
                rect.up_left.x--;
                rect.down_right.x++;
                print_new_sides(&rect, horizontal, CHR_RECT);
            }
            break;

        case KEY_LEFT:
            if (rect.down_right.x - rect.up_left.x > 1) {
                print_new_sides(&rect, horizontal, CHR_EMPTY);
                rect.up_left.x++;
                rect.down_right.x--;
            }
            break;

        case KEY_UP:
            if (rect.up_left.y > 0 && rect.down_right.y < row - 1) {
                rect.up_left.y--;
                rect.down_right.y++;
                print_new_sides(&rect, vertical, CHR_RECT);
            }
            break;

        case KEY_DOWN:
            if (rect.down_right.y - rect.up_left.y > 1) {
                print_new_sides(&rect, vertical, CHR_EMPTY);
                rect.up_left.y++;
                rect.down_right.y--;
            }
            break;

        case KEY_RESIZE:
            handle_resize(&row, &col, &rect);
            break;
        }
    }

    endwin();
    return 0;
}

void print_full_rect(const rectangle *r)
{
    int x, y;
    for (y = r->up_left.y; y <= r->down_right.y; y++)
        for (x = r->up_left.x; x <= r->down_right.x; x++)
            mvaddch(y, x, CHR_RECT);
    refresh();
}

void handle_resize(int *row, int *col, rectangle *r)
{
    int need_rebuild = 0;

    getmaxyx(stdscr, *row, *col);
    if (r->down_right.x >= *col) {
        r->down_right.x = *col - 1;
        need_rebuild++;
    }
    if (r->down_right.y >= *row) {
        r->down_right.y = *row - 1;
        need_rebuild++;
    }

    if (need_rebuild) {
        clear();
        print_full_rect(r);
    }
}

void print_new_sides(const rectangle *r, enum sides side, int chr)
{
    switch (side) { /* if-else too slowly */
    case horizontal: { /* bracket for legacy support */
        const int right = r->down_right.x;
        const int left  = r->up_left.x;
        int y = r->up_left.y;
        for ( ; y <= r->down_right.y; y++) {
            mvaddch(y, left, chr);
            mvaddch(y, right, chr);
        }
        break;

    } case vertical: { /* bracket for legacy support */
        const int down = r->down_right.y;
        const int up   = r->up_left.y;
        int x = r->up_left.x;
        for ( ; x <= r->down_right.x; x++) {
            mvaddch(up, x, chr);
            mvaddch(down, x, chr);
        }
        break;

    } default:
        endwin();
        fprintf(stderr, "print_new_sides: unknown side: %d", side);
        exit(200);
        break;
    }
    refresh();
}
