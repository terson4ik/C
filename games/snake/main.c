/* snake: support modern and legacy terminals, check common_types.h to
 * override ENTER */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "common_types.h"
#include "snake.h"
#include "tui.h"

#define KEY_ESCAPE      27
#define DELAY_TIME_EASY 130
#define DELAY_TIME_NORM 50
#define DELAY_TIME_HARD 30

int main(void)
{
    /* game init */
    snake *snake_head; /* AUTO_INIT, NULL not needed */
    point apple, game_field;
    int key, delay_time, i;

    initscr();
    start_color();
    if (has_colors())
        init_my_pairs();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    srand(time(NULL));

    getmaxyx(stdscr, game_field.y, game_field.x);
    if (game_field.y < MIN_SIZE_WINDOW || game_field.x < MIN_SIZE_WINDOW) {
        endwin();
        fprintf(stderr, "Too small window. set %d+ size\n", MIN_SIZE_WINDOW);
        return ERROR_CODE;
    }

    switch (start_game(&game_field, INIT_SIZE+1)) {
    case easy:   delay_time = DELAY_TIME_EASY; break;
    case normal: delay_time = DELAY_TIME_NORM; break;
    case hard:   delay_time = DELAY_TIME_HARD; break;
    default:
        endwin();
        fputs("main: unknonw level\n", stderr);
        return ERROR_CODE;
    }
    timeout(delay_time);
    if (snake_init(&snake_head, &game_field) == ERROR) {
        endwin();
        perror("snake_init");
        return ERROR_CODE;
    }
    draw_char(get_head_point(snake_head), CHR_SN_HEAD, HEAD_PAIR);
    for (i = INIT_SIZE; i > 0; i--) {
        if (snake_lengthen(snake_head, &game_field) == ERROR) {
            endwin();
            fputs("snake_lengthen: impossible increment\n", stderr);
        }
        draw_char(get_tail_point(snake_head), CHR_SN_BODY, BODY_PAIR);
    }
    snake_spawn_apple(snake_head, &apple, &game_field);
    draw_char(&apple, CHR_APPLE, APPLE_PAIR);

    /* game loop */
    while ((key = getch()) != KEY_ESCAPE && key != 'q' && key != 'Q') {
        point *head_p;
        switch (key) {
        case 'w':
        case 'W':
        case KEY_UP:    snake_change_side(snake_head, UP);    break;
        case 's':
        case 'S':
        case KEY_DOWN:  snake_change_side(snake_head, DOWN);  break;
        case 'a':
        case 'A':
        case KEY_LEFT:  snake_change_side(snake_head, LEFT);  break;
        case 'd':
        case 'D':
        case KEY_RIGHT: snake_change_side(snake_head, RIGHT); break;

        case KEY_ENTER:
        case ' ':
        case 'p':
        case 'P':
            timeout(-1);
            getch();
            timeout(delay_time);
            break;
        case KEY_RESIZE:
            getmaxyx(stdscr, game_field.y, game_field.x);
            if (handle_resize(snake_head, &game_field) == ERROR) {
                    fputs("Shit! You killed snake because small screen absorbed his"
            " body and she die :((\n", stderr);
                    return ERROR_CODE;
            }
            rebuild_game(&game_field, snake_get_size(snake_head));
        /* case ERR and default skip */
        }
        draw_char(get_head_point(snake_head), CHR_SN_BODY, BODY_PAIR);
        draw_char(get_tail_point(snake_head), CHR_EMPTY, BG_PAIR);
        snake_move(snake_head); /* check will be going in init game */
        draw_char(get_head_point(snake_head), CHR_SN_HEAD, HEAD_PAIR);

        move(0, 11); /* hide cursor if no colors */
        
        head_p = get_head_point(snake_head);
        if (apple.x == head_p->x && apple.y == head_p->y) {
            if (snake_lengthen(snake_head, &game_field)) {
                endwin();
                fputs("snake_lengthen: impossible increment\n", stderr);
            }
            snake_spawn_apple(snake_head, &apple, &game_field);
            draw_char(&apple, CHR_APPLE, APPLE_PAIR);
            update_stats(&game_field, snake_get_size(snake_head));
        } else 
        if (snake_check_hit(head_p, get_after_head_segm(snake_head))
         || snake_check_bounds(snake_head, &game_field)) {
            end_game(&game_field, snake_get_size(snake_head), 0);
            break;
        } else
        if (snake_is_win(snake_head, &game_field)) {
            end_game(&game_field, snake_get_size(snake_head), 1);
            break;
        }
    }

    endwin();
    snake_destroy(&snake_head);
    return 0;
}
