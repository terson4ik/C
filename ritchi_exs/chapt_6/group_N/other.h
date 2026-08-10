#ifndef MY_OTHER_H
#define MY_OTHER_H

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_space(c) ((c) == ' ' || (c) == '\n' || (c) == '\t')
#define is_alpha(c) ((((c) >= 'a' && (c) <= 'z')) || ((c) >= 'A' && (c) <= 'Z'))

#define is_alnum(c) ((((c) >= 'a' && (c) <= 'z')) || \
                      ((c) >= 'A' && (c) <= 'Z') || \
                      ((c) >= '0' && (c) <= '9'))
int strtoi(const char *s);
int getword(char *buf, int limit);

#endif
