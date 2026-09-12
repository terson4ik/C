#include <curses.h>
#include <unistd.h>
#include "tui.h"

int start_game(point *game_field, int size)
{
    if (has_colors()) {
        /* paint to red */
    }
    rebuild_game(game_field, size);
    return 0;
}

void update_stats(point *game_field, int size)
{
    mvprintw(0, 0, "length:%d    ", size);
    refresh();
}

void end_game(point *game_field, int size, int is_win)
{
    const int medianX = game_field->x / 2 - 7;
    const int medianY = game_field->y / 2;
    int key;

    clear();

    if(is_win) {
        mvaddstr(medianY, medianX, "WTF!?");
        mvaddstr(medianY+1, medianX, "WOW!!!");
        mvaddstr(medianY+2, medianX, "YOU WIN!!!");
    } else {
        mvaddstr(medianY, medianX, "YOU DIE :(");
        mvaddstr(medianY+1, medianX, "BUT!!!");
        mvprintw(medianY+2, medianX, "YOUR LENGTH BEFORE DIE:%d!", size);
    }
    refresh();
    timeout(0);
    while ((key = getch()) != KEY_ENTER) {
        if (key == KEY_RESIZE) {
            getmaxyx(stdscr, game_field->y, game_field->x);
            end_game(game_field, size, is_win);
            break;
        }
        mvaddstr(medianY+3, medianX, "PRESS ENTER TO CONTINUE...");
        refresh();
        usleep(10000);
        mvaddstr(medianY+3, medianX, "                          ");
        refresh();
        usleep(10000);
    }
}

void rebuild_game(point *game_field, int size)
{
    int x, y;

    for (x = 0, y = game_field->y-1; x < game_field->x; x++) {
        mvaddch(0, x, CHR_HORIZONTAL);
        mvaddch(y, x, CHR_HORIZONTAL);
    }

    for (y = 0, x = game_field->x-1; y < game_field->y; y++) {
        mvaddch(y, 0, CHR_VERTICAL);
        mvaddch(y, x, CHR_VERTICAL);
    }

    update_stats(game_field, size);
}