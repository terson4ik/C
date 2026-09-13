#include <curses.h>
#include "tui.h" /* common types also included here */

void init_my_pairs()
{
    init_pair(BORDER_PAIR, COLOR_BLACK,   COLOR_RED);
    init_pair(BG_PAIR,     COLOR_CYAN,    COLOR_CYAN);
    init_pair(HEAD_PAIR,   COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(BODY_PAIR,   COLOR_GREEN,   COLOR_GREEN);
    init_pair(APPLE_PAIR,  COLOR_RED,     COLOR_RED);
    init_pair(WIN_PAIR,    COLOR_GREEN,   COLOR_GREEN);
    init_pair(LOSE_PAIR,   COLOR_RED,     COLOR_RED);
}

static void draw_rect(int lx, int uy, int rx, int dy)
{
    int x, y;
    for (x = lx; x < rx; x++)
        for (y = uy; y < dy; y++)
            mvaddch(y, x, CHR_EMPTY);
    refresh();
}

void rebuild_game(point *game_field, int size)
{
    int x, y;
    clear();

    if (has_colors()) {
        attrset(COLOR_PAIR(BORDER_PAIR));
    } else {
        attrset(A_REVERSE);
    }
    for (x = 0, y = game_field->y-1; x < game_field->x; x++) {
        mvaddch(0, x, CHR_HORIZONTAL);
        mvaddch(y, x, CHR_HORIZONTAL);
    }

    for (y = 0, x = game_field->x-1; y < game_field->y; y++) {
        mvaddch(y, 0, CHR_VERTICAL);
        mvaddch(y, x, CHR_VERTICAL);
    }


    if (has_colors()) {
        attrset(COLOR_PAIR(BG_PAIR));
        draw_rect(1, 1, game_field->x-1, game_field->y-1);
        attrset(COLOR_PAIR(COMMON_PAIR));
    } else {
        attroff(A_REVERSE);
    }
    update_stats(game_field, size);
}

void end_game(point *game_field, int size, int is_win)
{
    const int medianX = game_field->x / 2 - 7;
    const int medianY = game_field->y / 2;
    int key;

    clear();
    attrset(A_REVERSE);
    if(is_win) {
        if (has_colors()) {
            attron(COLOR_PAIR(WIN_PAIR));
            draw_rect(0, 0, game_field->x, game_field->y);
            attroff(COLOR_PAIR(WIN_PAIR));
            attron(COLOR_PAIR(COMMON_PAIR));
       }
        mvaddstr(medianY, medianX, "WTF!?");
        mvaddstr(medianY+1, medianX, "WOW!!!");
        mvaddstr(medianY+2, medianX, "YOU WIN!!!");
    } else {
        if (has_colors()) {
            attron(COLOR_PAIR(LOSE_PAIR));
            draw_rect(0, 0, game_field->x, game_field->y);
            attroff(COLOR_PAIR(LOSE_PAIR));
            attron(COLOR_PAIR(COMMON_PAIR));
       }
        mvaddstr(medianY, medianX, "YOU DIE :(");
        mvaddstr(medianY+1, medianX, "BUT!!!");
        mvprintw(medianY+2, medianX, "YOUR LENGTH BEFORE DIE %dcm!", size);
    }
    refresh();
    timeout(-1);
    attrset(A_BLINK | A_BOLD | A_UNDERLINE);
    mvaddstr(medianY+3, medianX, "PRESS ENTER TO CONTINUE...");
    refresh();
    while ((key = getch()) != KEY_ENTER)
        if (key == KEY_RESIZE) {
            getmaxyx(stdscr, game_field->y, game_field->x);
            end_game(game_field, size, is_win);
            break;
        }
    attroff(A_BLINK | A_BOLD | A_UNDERLINE);
}

static enum levels menu(point *game_field)
{
    enum levels lvl = normal;
    const int medianX = game_field->x / 2 - 4;
    const int medianY = game_field->y / 2;
    int key;

    attrset(A_UNDERLINE | A_BLINK | A_DIM);
    mvaddstr(medianY-1, medianX, "CHOOSE LEVEL(TYPE ENTER)");
    attrset(A_BOLD);
    mvaddstr(medianY, medianX, "EASY :)))");
    mvaddstr(medianY+1, medianX, "NORMAL");
    mvaddstr(medianY+2, medianX, "HARD :(");
    attron(A_REVERSE);
    mvaddstr(medianY+1, medianX, "NORMAL");
    refresh();
    timeout(-1);
    while ((key = getch()) != KEY_ENTER) {
        attrset(A_BOLD);
        switch (key) {
        case KEY_UP:
            if (lvl != easy) {
                mvaddstr(medianY+lvl, medianX, (lvl == hard) ? "HARD :(" : "NORMAL");                
                lvl--;
                attron(A_REVERSE);
                mvaddstr(medianY+lvl, medianX, (lvl == easy) ? "EASY :)))" : "NORMAL");    
            }
            break;
        case KEY_DOWN:
            if (lvl != hard) {
                mvaddstr(medianY+lvl, medianX, (lvl == easy) ? "EASY :)))" : "NORMAL");         
                lvl++;
                attron(A_REVERSE);
                mvaddstr(medianY+lvl, medianX, (lvl == hard) ? "HARD :(" : "NORMAL");     
            }
            break;
        case KEY_RESIZE:
            clear();
            return menu(game_field);
        }
        refresh();
    }
    return lvl;
}

enum levels start_game(point *game_field, int size)
{
    enum levels lvl = menu(game_field);
    rebuild_game(game_field, size);
    return lvl;
}

void update_stats(point *game_field, int size)
{
    attrset(A_REVERSE);
    mvprintw(0, 0, "length:%d    ", size);
    attroff(A_REVERSE);
    refresh();
}
