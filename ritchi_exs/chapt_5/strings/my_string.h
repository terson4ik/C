#ifndef MY_STRING_H_SENTRY
#define MY_STRING_H_SENTRY

#include <stddef.h> /* for type size_t */
char *strncopy(char *dst, const char *src, size_t size);
char *strncaten(char *dst, const char *src, size_t size);
int   strncomp(const char *s1, const char *s2, size_t n);

#endif
