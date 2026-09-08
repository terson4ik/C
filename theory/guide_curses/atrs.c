#include <curses.h>
#include <unistd.h>

int main()
{
    int work_bw;
    initscr();
    work_bw = !has_colors();
    if (!work_bw)
        start_color();
    attron(A_BOLD);
    move(0, 0);
    addstr("Hello, ");
    attron(A_UNDERLINE);
    addstr("wonderful");
    attroff(A_BOLD | A_UNDERLINE);
    addstr(" world!");
    addch('*' | A_BOLD | A_BLINK);
    addch('*');
    move(1, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attrset(COLOR_PAIR(1) | A_UNDERLINE);
    addstr("White in blue");
    refresh();
    sleep(5);
    
    endwin();
    return 0;
}
