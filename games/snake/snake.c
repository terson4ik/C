#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "snake.h"

struct segment_of_snake_tag {
    point cur_p;
    struct segment_of_snake_tag *prev, *next;
};

struct snake_tag {
    segment_snake *head, *tail;
    unsigned int length;
    enum sides side;
};
 /* typedef defined in header file */

void snake_init(snake **s, int init_size, point *game_field)
{
    segment_snake *head;
    *s = malloc(sizeof(**s));
    head = malloc(sizeof(*head));
    if (!*s || !head) {
        endwin();
        perror("snake_init");
        exit(200);
    }
    srand(time(NULL));
    (*s)->side = (rand() + 1) % 4;
    (*s)->length = 1;
    head->cur_p.x = game_field->x / 2;
    head->cur_p.y = game_field->y / 2;
    head->next = head->prev = (*s)->head = (*s)->tail = head;

    if (has_colors())
        attrset(COLOR_PAIR(HEAD_PAIR));
    mvaddch((*s)->head->cur_p.y, (*s)->head->cur_p.x, CHR_SN_HEAD);
    if (has_colors())
        attrset(COLOR_PAIR(BODY_PAIR));
    while (--init_size > 0) {
        snake_lengthen(*s, game_field);
        mvaddch((*s)->tail->cur_p.y, (*s)->tail->cur_p.x, CHR_SN_BODY);
    }
}

void snake_move(snake *s) 
{
    if (has_colors())
        attrset(COLOR_PAIR(BG_PAIR));
    mvaddch(s->tail->cur_p.y, s->tail->cur_p.x, CHR_EMPTY);

    s->tail->cur_p = s->head->cur_p;
    s->head = s->tail;
    s->tail = s->head->prev;

    switch(s->side) {
    case UP:    s->head->cur_p.y--; break;
    case DOWN:  s->head->cur_p.y++; break;
    case LEFT:  s->head->cur_p.x--; break;
    case RIGHT: s->head->cur_p.x++; break;
    default:
        endwin();
        fputs("snake_move: no such case, fatal error\n", stderr);
        exit(200);
    }
    if (has_colors())
        attrset(COLOR_PAIR(BODY_PAIR));
    if (s->head->next != NULL)
        mvaddch(s->head->next->cur_p.y, s->head->next->cur_p.x, CHR_SN_BODY);
    if (has_colors())
        attrset(COLOR_PAIR(HEAD_PAIR));
    mvaddch(s->head->cur_p.y, s->head->cur_p.x, CHR_SN_HEAD);
    refresh();
}

void handle_resize(snake *s, point *game_field)
{
    if (snake_check_hit(game_field, s->head)) {
        endwin();
        fputs("Shit! You killed snake because small screen absorbed his"
            " body and she die :((\n", stderr);
        exit(1);
    }
}

int  snake_check_hit(const point *head, const segment_snake *next) 
{
    const segment_snake *anchor = next->prev; /* TRUE head */
    while (next != anchor) {
        if (head->x == next->cur_p.x && head->y == next->cur_p.y)
            return 1;
        next = next->next;
    } 
    return 0;
}

void snake_spawn_apple(const snake *s, point *app, point *game_field) 
{
    do {
        app->x = (rand() % (game_field->x-2)) + 1;
        app->y = (rand() % (game_field->y-2)) + 1;
    } while (snake_check_hit(app, s->head->next));
    if (has_colors())
        attrset(COLOR_PAIR(APPLE_PAIR));
    mvaddch(app->y, app->x, CHR_APPLE);
    refresh();
}

int snake_check_bounds(const snake *h, point *game_field) 
{
    return h->head->cur_p.x < 1 || h->head->cur_p.x >= game_field->x-1
        || h->head->cur_p.y < 1 || h->head->cur_p.y >= game_field->y-1;
}
void snake_change_side(snake *s, enum sides new_side)
{
    switch (new_side) {
    case UP:    if (s->side != DOWN)  s->side = UP;    break;
    case DOWN:  if (s->side != UP)    s->side = DOWN;  break;
    case LEFT:  if (s->side != RIGHT) s->side = LEFT;  break;
    case RIGHT: if (s->side != LEFT)  s->side = RIGHT; break;
    default:
        endwin();
        fputs("snake_change_side: no such case, fatal error\n", stderr);
        exit(200);
    }
}

void snake_lengthen(snake *s, point *game_field)
{
    segment_snake *new_segm = malloc(sizeof(*new_segm));
    if (!new_segm) {
        endwin();
        perror("snake_lengthen");
        exit(200);
    }

    switch (s->side) {
    case UP:
        new_segm->cur_p.x = s->tail->cur_p.x;
        new_segm->cur_p.y = s->tail->cur_p.y + 1;
        break;
    case DOWN:
        new_segm->cur_p.x = s->tail->cur_p.x;
        new_segm->cur_p.y = s->tail->cur_p.y - 1;
        break;
    case LEFT:
        new_segm->cur_p.x = s->tail->cur_p.x + 1;
        new_segm->cur_p.y = s->tail->cur_p.y;
        break;
    case RIGHT:
        new_segm->cur_p.x = s->tail->cur_p.x - 1;
        new_segm->cur_p.y = s->tail->cur_p.y;
        break;
    default:
        endwin();
        fputs("snake_lengthen: no such case, fatal error\n", stderr);
        exit(200);
    }

    if (new_segm->cur_p.x < 0 || new_segm->cur_p.x >= game_field->x ||
        new_segm->cur_p.y < 0 || new_segm->cur_p.y >= game_field->y) {
        endwin();
        fputs("snake_lengthen: impossible increment\n", stderr);
        exit(200);
    }

    s->length++;
    new_segm->next = s->head;
    new_segm->prev = s->tail;
    s->tail->next = new_segm;
    s->tail = new_segm;
    s->head->prev = s->tail;
}

int snake_is_win(const snake *s, point *game_field)
{
    return s->length >= (game_field->x-2) * (game_field->y-2);
}

point *get_head_point(const snake *s)
{
    return &s->head->cur_p;
}

segment_snake *get_head_segm(const snake *s)
{
    return s->head;
}

segment_snake *get_after_head_segm(const snake *s)
{
    return s->head->next;
}

int snake_get_size(const snake *s)
{
    return s->length;
}

void snake_destroy(snake **s) 
{
    (*s)->tail->next = NULL;
    while ((*s)->head != NULL) {
        segment_snake *cur = (*s)->head;
        (*s)->head = (*s)->head->next;
        free(cur);
    }
    free(*s);
    *s = NULL;
}
