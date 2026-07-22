/* legacy function using buffer, then if you use ungets, using LEGACY func */
#ifndef GETCH_H_SENTRY
#define GETCH_H_SENTRY
int getch();
void ungetch(int c);
int get_not_space();
int legacy_getch();
void legacy_ungetch(int c);
void ungets(char *s);

#endif
