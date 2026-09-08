#include <curses.h>
#include <unistd.h>

static const char msg[] = "Hello world!";
enum { key_escape = 27 };

static void show_message(int x, int y)
{
 /* move(0, 0);
    printw("(%d,%d)    ", x, y); */
        /* btw, this y, x */
    mvprintw(0, 0, "(%d, %d)    ", x, y);
    move(y, x);
    addstr(msg);
    refresh();
}
static void hide_message(int x, int y)
{
    int i;
    move(y, x);
                   /* minus \0 */
    for (i = sizeof(msg) - 1; i > 0; i--)
        addch(' ');
    refresh();
}
static void check(int *coord, int max)
{
    if (*coord < 0)
        *coord = 0;
    else
    if (*coord > max)
        *coord = max;
}
static void
move_message(int *x, int *y, int mx, int my, int dx, int dy)
{
    hide_message(*x, *y);
    *x += dx;
    check(x, mx);
    *y += dy;
    check(y, my);
    show_message(*x, *y);
}
static void handle_resize(int *x, int *y, int *mx, int *my)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    *mx = col - sizeof(msg) + 1;
    *my = row - 1;
    hide_message(*x, *y);
    check(x, *mx);
    check(y, *my);
    show_message(*x, *y);
}
int main()
{
    int row, col, x, y, max_x, max_y, key;
    initscr();
    cbreak(); /* non canonic mode */
    keypad(stdscr, 1); /* enable support up left down rigth and F1...F12 */
    noecho(); /* don't print chars if key pressed */
    curs_set(0); /* remove cursor */
    getmaxyx(stdscr, row, col);
    x = (col-sizeof(msg)-1)/2;
    y = row / 2;
    max_x = col - sizeof(msg) + 1;
    max_y = row - 1;
    show_message(x, y);
    while ((key = getch()) != key_escape) {
        switch (key) {
            case KEY_UP:
                move_message(&x, &y, max_x, max_y, 0, -1);
                break;
            case KEY_RIGHT:
                move_message(&x, &y, max_x, max_y, 1, 0);
                break;
            case KEY_DOWN:
                move_message(&x, &y, max_x, max_y, 0, 1);
                break;
            case KEY_LEFT:
                move_message(&x, &y, max_x, max_y, -1, 0);
                break;
            case KEY_RESIZE:
                handle_resize(&x, &y, &max_x, &max_y);
                break;
        }
    }

    endwin();
    return 0;
}
