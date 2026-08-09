#ifndef MY_STRING_H
#define MY_STRING_H

unsigned int str_len(const char *s);
char *str_dup(const char *s);
char *str_cpy(char *dst, const char *src);
int str_cmp(const char *s1, const char *s2);

#endif
