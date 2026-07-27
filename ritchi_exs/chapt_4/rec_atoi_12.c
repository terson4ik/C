#include <stdio.h>

#ifndef FAST
#  define FAST 1
#endif
#if FAST
void itoa(int x, char *str);
int itoa_rec(int x, char *str);
#else
int itoa(int x, char *str);
#endif

#define MAX_LINE 33
int main()
{
    char line[MAX_LINE];
    int x, diag;

    while ((diag = scanf("%d", &x)) == 1) {
        itoa(x, line);
        printf("%s\n", line);
    }
    if (diag != EOF) {
        fprintf(stderr, "invalid input\n");
        return 1;
    }
    return 0;
}

#if FAST
void 
#else
int
#endif
itoa(int x, char *str)
{
#if FAST
    str[itoa_rec(x, str)] = '\0';
#else
    int pos, tmp;

    pos = 0;
    if (x / 10)
        pos = itoa(x / 10, str);
    if (pos == 0 && x < 0 )
        str[pos++] = '-';
    tmp = x % 10;
    str[pos] = ((tmp < 0) ? -tmp : tmp) + '0';
    str[++pos] = '\0';
    return pos;
#endif
}
#if FAST
int itoa_rec(int x, char *str)
{
    /* 123 = 321 */
    int pos, tmp;

    pos = 0;
    if (x / 10)
        pos = itoa_rec(x / 10, str);
    if (pos == 0 && x < 0 )
        str[pos++] = '-';
    tmp = x % 10;
    str[pos] = ((tmp < 0) ? -tmp : tmp) + '0';
    return pos + 1;
}
#endif
