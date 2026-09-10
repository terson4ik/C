/* square + runner dog; simple version */
#include <stdio.h>
#include <curses.h>

#define DELAY_TIME 100
#define SQR_SIZE   10
#define SMALL_SIZE (2 + SQR_SIZE)
#define CHR_RUNNER '#'
#define CHR_RECT   '*'

typedef struct point_tag {
    int x, y;
} point;

typedef struct rect_tag {
    point up_lft, down_rgt;
} rect;

void print_ch(int c, const point *p);
void make_square(const point *lu);
void move_runner(point *r, const rect *sqr);

int main()
{
    int row, col;
    point r;
    rect sqr;

    initscr();
    curs_set(0);
    cbreak();
    noecho();
    timeout(DELAY_TIME);

    getmaxyx(stdscr, row, col);
    if (col < SMALL_SIZE || row < SMALL_SIZE) {
        endwin();
        fputs("Too small window.\n", stderr);
        return 1;
    }
    sqr.up_lft.x = (col/2) - (SQR_SIZE/2);
    sqr.up_lft.y = (row/2) - (SQR_SIZE/2);
    sqr.down_rgt.x = sqr.up_lft.x + SQR_SIZE - 1;
    sqr.down_rgt.y = sqr.up_lft.y + SQR_SIZE - 1;
    r = sqr.up_lft;

    make_square(&sqr.up_lft);
    print_ch(CHR_RUNNER, &r);
    while (getch() == ERR)
        move_runner(&r, &sqr);

    endwin();
    return 0;
}

void print_ch(int c, const point *p)
{
    move(p->y, p->x);
    addch(c);
    refresh();
}

void make_square(const point *lu)
{
    int x, y;
    for (x = lu->x; x < lu->x+SQR_SIZE; x++)
        for (y = lu->y; y < lu->y+SQR_SIZE; y++) {
            move(y, x);
            addch(CHR_RECT);
        }
    refresh();
}

void move_runner(point *r, const rect *sqr)
{
    print_ch(CHR_RECT, r);

    if (r->y == sqr->up_lft.y && r->x < sqr->down_rgt.x)
        r->x++;
    else if (r->x == sqr->down_rgt.x && r->y < sqr->down_rgt.y)
        r->y++;
    else if (r->y == sqr->down_rgt.y && r->x > sqr->up_lft.x)
        r->x--;
    else
        r->y--;

    print_ch(CHR_RUNNER, r);
}
