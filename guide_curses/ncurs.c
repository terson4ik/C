#include <curses.h>
#include <unistd.h>

const char msg[] = "Hello world!";
enum { duration_t = 5 };

int main()
{
    int row, col;
    initscr();
    getmaxyx(stdscr, row, col);
    move(row/2, (col- sizeof(msg))/2);
    addstr(msg);
    curs_set(0);
    refresh();
    sleep(duration_t);
    endwin();
    return 0;
}
