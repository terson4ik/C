#ifndef SNAKE_SENTRY_HEADER
#define SNAKE_SENTRY_HEADER

#include "common_types.h"

enum sides { UP = 0, DOWN, LEFT, RIGHT };

typedef struct snake_tag snake;
typedef struct segment_of_snake_tag segment_snake;

void snake_init(snake **s, int init_size, point *game_field);
void snake_move(snake *s);
void snake_change_side(snake *s, enum sides new_side);
void snake_destroy(snake **s);
void handle_resize(snake *s, point *game_field);
point *get_head_point(const snake *s);
segment_snake *get_head_segm(const snake *s);
segment_snake *get_after_head_segm(const snake *s);
int snake_get_size(const snake *s);
 /* use also to spawn apple */
int snake_check_hit(const point *head, const segment_snake *next);

int snake_check_bounds(const snake *s, point *game_field) ;
void snake_lengthen(snake *s, point *game_field);
void snake_spawn_apple(const snake *s, point *apple, point *game_field);
int snake_is_win(const snake *s, point *game_field);

#endif
