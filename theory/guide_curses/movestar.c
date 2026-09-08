#include <curses.h>

enum { delay_duration = 100, key_escape = 27 };
typedef struct star_tag {
    int x, y, dx, dy;
} Star;

static void show_star(const Star *s)
{
    move(s->y, s->x);
    addch('*');
    refresh();
}

static void hide_star(const Star *s)
{
    move(s->y, s->x);
    addch(' ');
    refresh();
}

static void check(int *coord, int max)
{
    if (*coord < 0)
        *coord += max;
    else
    if (*coord > max)
        *coord -= max;
}

static void move_star(Star *s, int max_x, int max_y)
{
    hide_star(s);
    s->x += s->dx;
    check(&s->x, max_x);
    s->y += s->dy;
    check(&s->y, max_y);
    show_star(s);
}

static void set_direction(Star *s, int dx, int dy)
{
    s->dx = dx;
    s->dy = dy;
}

static void handle_resize(Star *s, int *col, int *row)
{
    getmaxyx(stdscr, *col, *row);
    if (s->x > *col)
        s->x = *col;
    if (s->y > *row)
        s->y = *row;
}

int main()
{
    int key, row, col;
    Star s;
    initscr();
    timeout(delay_duration);
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    getmaxyx(stdscr, row, col);
    s.x = col / 2;
    s.y = row / 2;
    set_direction(&s, 0, 0);
    while ((key = getch()) != key_escape)
        switch(key) {
        case KEY_UP:
            set_direction(&s, 0, -1);
            break;
        case KEY_DOWN:
            set_direction(&s, 0, 1);
            break;
        case KEY_LEFT:
            set_direction(&s, -1, 0);
            break;
        case KEY_RIGHT:
            set_direction(&s, 1, 0);
            break;
        case ' ':
            set_direction(&s, 0, 0);
            break;
        case ERR:
            move_star(&s, col-1, row-1);
            break;
        case KEY_RESIZE:
            handle_resize(&s, &col, &row);
            break;
        }
    endwin();
    return 0;
}
