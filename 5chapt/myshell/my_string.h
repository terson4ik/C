#ifndef MY_STRING_H_SENTRY
#define MY_STRING_H_SENTRY

#include <stdlib.h> /* necessary to free() in user program */

size_t mstrlen(const char *s);
void mstrcpy(char *dst, const char *src);
char *mstrdup(const char *s);
void mstrcat(char *head, const char *tail);
int mstrcmp(const char *s1, const char *s2);
char *mstrstr(const char *s1, const char *s2);
char *mstr_realloc(char *s, size_t new_size);

#endif
