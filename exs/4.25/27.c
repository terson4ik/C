/* funny ball with exit */
#include <stdio.h> /* NULL */
#include <stdlib.h> /* rand */
#include <time.h> /* part of rand */
#include <curses.h>


#define DELAY_TIME 100 /* 1 millisec = 0.001s; 100 = 1/10s  */
#define MAX_LOOP 3

struct point {
    int x, y;
    enum { left, right } direct;
};

static void print_ch(char c, int x, int y);
int move_star(struct point *p, int max_x);

int main()
{
    struct point p;
    int times, row, col;

    initscr();
    cbreak();
    curs_set(0);
    timeout(DELAY_TIME);
    srand(time(NULL));

    getmaxyx(stdscr, row, col);
    p.x = col / 2;
    p.y = row / 2;
    p.direct = (rand() % 2) == 0 ? left : right;
    times = 1 + MAX_LOOP*2; /* if need 1 cirlce then 3 touches need */

    print_ch('*', p.x, p.y);
    while (times && (getch() == ERR))
        if (move_star(&p, col-2)) /* touch */
            times--;

    endwin();
    return 0;
}

static void print_ch(char c, int x, int y)
{
    move(y, x);
    addch(c);
    refresh();
}

int move_star(struct point *p, int max_x)
{
    int is_touch = 0;

    print_ch(' ', p->x, p->y);
    if (p->x <= 0 || p->x >= max_x) {
        is_touch = 1;
        p->direct = p->direct == left ? right : left;
    }
    p->x += (p->direct == left) ? -1 : 1;
    
    print_ch('*', p->x, p->y);
    return is_touch;
}
