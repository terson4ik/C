#ifndef OTHER_H_SENTRY
#define OTHER_H_SENTRY

int get_line(char *s, int lim);
double atof(const char *s);
int    atoi(const char *s);
char   *itoa(int num, char *dst);
char   *itob(int num, char *dst);
void   reverse(char *s);
int    strindex(const char *s1, const char *s2);

int rec_atoi(const char *s);
void rec_itoa(int num, char *dst);
void rec_rev(char *s);
#endif
