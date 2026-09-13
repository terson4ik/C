#ifndef TUI_SENTRY_HEADER
#define TUI_SENTRY_HEADER

#include "common_types.h"
#define CHR_HORIZONTAL '$'
#define CHR_VERTICAL '|'
enum levels { easy = 0, normal, hard };

enum levels start_game(point *game_field, int size);
void rebuild_game(point *game_field, int size);
void update_stats(point *game_field, int size);
void end_game(point *game_field, int size, int is_win);
void init_my_pairs();

#endif
