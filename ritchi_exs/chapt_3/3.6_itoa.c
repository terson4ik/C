#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <limits.h>
#endif

void itoa(int n, char s[], int l);
void reverse(char s[]);

int main()
{
    char *s = malloc(INT_WIDTH + 2); /* +1 for '\0' and + 1 to minus */
    int x, l, diag;
#if DEBUG
        itoa(INT_MIN, s, INT_WIDTH);
        printf("DEBUG\n%s\n-------\n", s);
#endif
    puts("Enter num(scanf give decimal) and width:");
    while((diag = scanf("%d %d", &x, &l)) == 2) {
        itoa(x, s, l);
        printf("-------\n%s\n-------\n", s);
    }

    if (diag != EOF) {
        fputs("INVALID INPUT\n", stderr);
        free(s);
        return 1;
    }

    free(s);
    return 0;
}

void itoa(int n, char s[], int l)
{
    int sign, i;

    sign = (n < 0) ? -1 : +1;
    i = 0;
    do {
        s[i++] = '0' + ((n < 0) ? -(n % 10) : +(n % 10));
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
    while (l > i)
        s[i++] = ' ';
    s[i] = '\0'; /* 321-___-> ___-123 */
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    for (j = 0; s[j]; j++) {
    }
    for (i = 0, j--; i < j; i++, j--) {
        register char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
