#include <stdio.h>
#include <ctype.h>

int getfloat(float *pf);

#define SIZE 5
int main()
{
    int n, i;
    float array[SIZE] = { 1 };
    for (i = 0; i < SIZE; i++)
        printf("arr[%d] = %.8g\n", i, array[i]);
    for (n = 0; n < SIZE && (getfloat(&array[n]) != EOF); n++)
        ;
    for (i = 0; i < n; i++)
        printf("arr[%d] = %.8g\n", i, array[i]);
}

int getch(void);
void ungetch(int c);
int getfloat(float *pf)
{
    int c, sign, expa, expa_sign;
    float pow;

    while (isspace(c = getch())) {
    }
    if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
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
    for (*pf = 0.0f; isdigit(c); c = getch())
        *pf = *pf * 10.0f + (c - '0');

    if(c == '.') {
        c = getch();
        if (!isdigit(c) && c != 'E' && c != 'e') {
            ungetch(c);
            return '.';
        }
    }
    for (pow = 1.0f; isdigit(c); c = getch()) {
        *pf = *pf * 10.0f + (c - '0');
        pow *= 10;
    }
    expa = 1;
    expa_sign = 1;
    if (c == 'E' || c == 'e') {
        int tmp, exp_base;
        tmp = c;
        c = getch();
        if (!isdigit(c) && c != '-' && c != '+') {
            ungetch(c);
            ungetch(tmp);
            *pf /= pow;
            return 0;
        }
        if (c == '-' || c == '+') {
            expa_sign = (c == '-') ? -1 : 1;
            c = getch();
        }

        for (exp_base = 0; isdigit(c); c = getch()) 
            exp_base = exp_base * 10 + c - '0';
        while (exp_base-- > 0) /* expa inits before if 'E') */
            expa *= 10;
    }
    if (expa_sign > 0)
    *pf = sign * *pf * (expa / pow);
    else
    *pf = sign * *pf / (expa * pow);

    ungetch(c);
    return c;
}

#define BUF_SIZE 15
static int buf[BUF_SIZE];
static int pbuf = 0;

int getch(void)
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
