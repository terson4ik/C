#include <stdio.h>
#include <ctype.h>

int getint(int *pn);

#define SIZE 5
int main()
{
    int n, i;
    int array[SIZE] = { 1 };
    for (i = 0; i < SIZE; i++)
        printf("arr[%d] = %d\n", i, array[i]);
    for (n = 0; n < SIZE && (getint(&array[n]) != EOF); n++)
        ;
    for (i = 0; i < n; i++)
        printf("arr[%d] = %d\n", i, array[i]);
}

int getch();
void ungetch(int c);
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
    if (c == '-' || c == '+') {
        int tmp = c;
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            ungetch(tmp);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + c - '0';
    *pn *= sign;
    ungetch(c);
    return c;
}

#define BUF_SIZE 15
static int buf[BUF_SIZE];
static int pbuf = 0;

int getch()
{
    return (pbuf > 0) ? buf[--pbuf] : getchar();
}
void ungetch(int c)
{
    if (pbuf < BUF_SIZE)
        buf[pbuf++] = c;
    else
        fputs("ungetch: buffer overflow\n", stderr);
}
