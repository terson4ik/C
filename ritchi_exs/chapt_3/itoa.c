#include <stdio.h>
#include <stdlib.h>

#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    char *s = malloc(INT_WIDTH + 1); /* +1 for '\0' */
/*
    int x, diag;
    puts("Enter num(scanf give decimal):");
    diag = scanf("%d", &x);
    if (diag != 1) {
        perror("Incorrect number.");
        return 1;
    }
*/
    itoa(INT_MIN, s);
    printf("%s\n", s); 
    itoa(-5, s);
    printf("%s\n", s); 
    itoa(46677, s);
    printf("%s\n", s); 
    free(s);
    return 0;
}

void itoa(int n, char s[])
/* because 10000 = 011111 + 1 = 100000- i'ts error. */
{
    int sign, i;
    unsigned int true_n = n;

    printf("%d\n", n);
    if ((sign = n) < 0)
        true_n = ~n + 1;

    i = 0;
    do {
        s[i++] = (n % 10 < 0) ? -(n % 10) + '0': n % 10 + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j, c;
    
    j = 0;
    while(s[j++] != '\0') {
    }
    j -= 2;
    for(i = 0; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}
