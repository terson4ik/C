#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <limits.h>
#endif

#define LETTER_A_IN_HEX  10
void itob(int n, char s[], int b);
void reverse(char s[]);

#define LETTER_A 'A' /* set 'a' or 'A' */
int main()
{
    char *s = malloc(INT_WIDTH + 2); /* +1 for '\0' and + 1 to minus */
    int x, b, diag;
#if DEBUG
    itob(INT_MIN, s, 10);
    printf("%s\n", s); 
    itob(-5, s, 2);
    printf("%s\n", s); 
    itob(46677, s, 16);
    printf("%s\n", s); 
    itob(15, s, 16);
    printf("%s\n", s); 
    itob(16, s, 16);
    printf("%s\n", s); 
#endif
    puts("Enter num(scanf give decimal) and base:");
    while((diag = scanf("%d %d", &x, &b)) == 2) {
        itob(x, s, b);
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

void itob(int n, char s[], int b)
{
    int i, sign;

    if (b <= 1 || b > 10 + 25 + 1) { /* 36 is max, Z is 36 base */
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    sign = (n < 0) ? -1 : 1;

    i = 0;
    do {
        int tmp = (n % b < 0) ? -(n % b) : +(n % b);
        s[i++] = (tmp >= LETTER_A_IN_HEX) ? (tmp - 10 + LETTER_A)
                                        :   (tmp + '0');
    } while ((n = (n / b)) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;

    j = 0;
    while (s[j] != '\0')
        j++;

    j--; /* index starts with 0 */
    for (i = 0; i < j; i++, j--) {
        int c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
