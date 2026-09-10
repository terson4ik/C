/* Square and running dog: extended version */
#include <stdio.h>  /* For errmsg */
#include <stdlib.h> /* exit() */
#include <unistd.h> /* usleep() */
#include <curses.h>

#define SQUARE_SIZE     10
#define SMALL_SIZE      (2 + SQUARE_SIZE)
#define SMALL_SIZE_MSG  "Screen too small, set %d+ size of term\n"
#define CHR_SQUERE      '*'
#define CHR_RUNNER      '#'
#define KEY_ESCAPE      27
#define MAX_USLEEP      1000000 /* 1s */
#define DELAY_TIME      (MAX_USLEEP / 10) /* 1/10 seconds */

typedef struct {
    int x, y;
} point;

typedef struct {
    point p;
    enum { clock_stp, anticlock_stp } direct;
} runner;

typedef struct {
    point up_lft, down_rgt;
} rectangle;

void print_pnt(int c, const point *p);
void handle_resize(rectangle *sqr, point *r);
void move_runner(runner *r, const rectangle *sqr);
static void make_square(const point *pt_sqr);

int main(void)
{
    int delay;
    rectangle sqr;
    runner r;

    initscr();
    curs_set(0);
    keypad(stdscr, 1);  /* arrows */
    timeout(0);         /* No wait */
    cbreak();
    noecho();

    handle_resize(&sqr, &r.p);
    delay = DELAY_TIME;
    while(1) {
        int key;
        while((key = getch()) != ERR) /* Clear buffer */
            switch(key) {
            case KEY_LEFT:
                delay *= (delay * 10 <= MAX_USLEEP) ? 10 : 1;
                break;
            case KEY_RIGHT:
                delay /= (delay / 10 >= 1) ? 10 : 1;
                break;
            case ' ':
                r.direct = (r.direct == clock_stp) ? anticlock_stp : clock_stp;
                break;
            case KEY_RESIZE:
                handle_resize(&sqr, &r.p); /* Don't save r.p.x and r.p.y */
                break;
            case KEY_ESCAPE:
                goto esc;
        }
        usleep(delay);
        move_runner(&r, &sqr);

    }
esc:
    endwin();
    return 0;
}

void print_pnt(int c, const point *p)
{
    move(p->y, p->x);
    addch(c);
    refresh();
}

static void make_square(const point *pt_sqr)
{
    int x, y;
    for (y = pt_sqr->y; y < pt_sqr->y + SQUARE_SIZE; y++)
        for (x = pt_sqr->x; x < pt_sqr->x + SQUARE_SIZE; x++) {
            move(y, x);
            addch(CHR_SQUERE);
        }
    refresh();
}

void handle_resize(rectangle *sqr, point *r)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    if (row < SMALL_SIZE || col < SMALL_SIZE) {
        endwin();
        fprintf(stderr, SMALL_SIZE_MSG, SQUARE_SIZE);
        exit(1);
    }

    sqr->up_lft.x   = (col/2) - (SQUARE_SIZE/2);
    sqr->up_lft.y   = (row/2) - (SQUARE_SIZE/2);
    sqr->down_rgt.x = sqr->up_lft.x + SQUARE_SIZE - 1;
    sqr->down_rgt.y = sqr->up_lft.y + SQUARE_SIZE - 1;
    *r = sqr->up_lft;

    clear();
    make_square(&sqr->up_lft);
}

void move_runner(runner *r, const rectangle *sqr)
{
    print_pnt(CHR_SQUERE, &r->p);

    /* hard_code algorithm */
    if (r->direct == clock_stp) {
        if (r->p.y == sqr->up_lft.y && r->p.x < sqr->down_rgt.x)
            r->p.x++;
        else if (r->p.x == sqr->down_rgt.x && r->p.y < sqr->down_rgt.y)
            r->p.y++;
        else if (r->p.y == sqr->down_rgt.y && r->p.x > sqr->up_lft.x)
            r->p.x--;
        else /* last case, if() not needed */
            r->p.y--;
    } else { /* anti_clock */
        if (r->p.x == sqr->up_lft.x && r->p.y < sqr->down_rgt.y)
            r->p.y++;
        else if (r->p.y == sqr->down_rgt.y && r->p.x < sqr->down_rgt.x)
            r->p.x++;
        else if (r->p.x == sqr->down_rgt.x && r->p.y > sqr->up_lft.y)
            r->p.y--;
        else /* last case, if() not needed */
            r->p.x--;
    }

    print_pnt(CHR_RUNNER, &r->p);
}
