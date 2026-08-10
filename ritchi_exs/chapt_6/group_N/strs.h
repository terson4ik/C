#ifndef MY_STR_H
#define MY_STR_H

unsigned int str_len(const char *s);
char *str_dup(const char *s);
char *str_n_dup(const char *s, int n);
char *str_cpy(char *dst, const char *src);
char *str_n_cpy(char *dst, const char *src, int n);
int str_cmp(const char *s1, const char *s2);
int str_n_cmp(const char *s1, const char *s2, int n);

#endif
