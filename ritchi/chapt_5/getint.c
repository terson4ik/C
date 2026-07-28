#include <stdio.h>
#include <ctype.h>

int getint(int *pn);

#define SIZE 5
int main()
{
    int n, i;
    int array[SIZE] = { 0 };
    for (i = 0; i < SIZE; i++)
        printf("arr[%d] = %d\n", i, array[i]);
    for (n = 0; n < SIZE && (getint(&array[n]) != EOF); n++)
        ;
    for (i = 0; i < n; i++)
        printf("arr[%d] = %d\n", i, array[i]);
}

int getch();
void ungetch(char c);
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != '-' && c != EOF && c != '+') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + c - '0';
    *pn *= sign;
    ungetch(c);
    return c;
}

static int last_c = EOF;

int getch()
{
    int temp = (last_c == EOF) ? getchar() : last_c;
    last_c = EOF;
    return temp;
}
void ungetch(char c)
{
    last_c = c;
}
