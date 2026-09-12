#ifndef COMMON_DATA_SENTRY_HEADER
#define COMMON_DATA_SENTRY_HEADER

#ifdef KEY_ENTER
#  undef KEY_ENTER
#  define KEY_ENTER '\n'
#else
#  define KEY_ENTER '\n'
#endif

struct point_tag{
    int x, y;
};
typedef struct point_tag point;

#endif