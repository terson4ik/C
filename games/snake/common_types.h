#ifndef COMMON_DATA_SENTRY_HEADER
#define COMMON_DATA_SENTRY_HEADER

#ifdef KEY_ENTER
#  undef KEY_ENTER
#  define KEY_ENTER '\n'
#else
#  define KEY_ENTER '\n'
#endif

#define INIT_SIZE   (1 + 3) /* head + 3 body */

#define CHR_SN_HEAD '@'
#define CHR_SN_BODY 'o'
#define CHR_APPLE   '&'
#define CHR_EMPTY   ' '
#define RECORD_FILE_NAME ".records.txt"

#define MIN_SIZE_WINDOW 15

enum pairs { COMMON_PAIR = 0, BORDER_PAIR, BG_PAIR,
             HEAD_PAIR, BODY_PAIR, APPLE_PAIR,  
             WIN_PAIR, LOSE_PAIR   
};

struct point_tag{
    int x, y;
};
typedef struct point_tag point;

#endif