#ifndef MY_STRING_H
#define MY_STRING_H

int my_numcmp(const char *s1, const char *s2);
int my_strcmp(const char *s1, const char *s2);
int my_strcasecmp(const char *s1, const char *s2);
int dir_cmp(const char *s1, const char *s2);
int dir_case_cmp(const char *s1, const char *s2);
int extract_fild(char *buf, const char *orig_s, int field);

void my_str_cpy(char *dst, const char *src);

#endif