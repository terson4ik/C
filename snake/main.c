#include <curses.h>
#include "snake.h"
#include "tui.h"

#define KEY_ESCAPE  27
#define DELAY_TIME  100

/* TODO: 
 * colors
 * levels
*/

int main(void)
{
    /* game init */
    snake *snake_head; /* AUTO_INIT, NULL not needed */
    point apple, game_field;
    int key;

    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, 1);
    timeout(DELAY_TIME);
    getmaxyx(stdscr, game_field.y, game_field.x);
    start_game(&game_field, INIT_SIZE);
    snake_init(&snake_head, INIT_SIZE, &game_field);

    snake_spawn_apple(snake_head, &apple, &game_field);

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
            timeout(DELAY_TIME);
            break;
        case KEY_RESIZE:
            getmaxyx(stdscr, game_field.y, game_field.x);
            handle_resize(snake_head, &game_field);
            rebuild_game(&game_field, snake_get_size(snake_head));
        /* case ERR and default skip */
        }
        snake_move(snake_head);

        head_p = get_head_point(snake_head);
        if (apple.x == head_p->x && apple.y == head_p->y) {
            snake_lengthen(snake_head, &game_field);
            snake_spawn_apple(snake_head, &apple, &game_field);
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
