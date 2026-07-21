#include <stdio.h>
#include <ctype.h>

int get_line(char s[], int lim);
double atof(char s[]);

#define MAX_LINE    1000
int main()
{
    double sum, atof(char []);
    char line[MAX_LINE];
    sum = 0;
    while (get_line(line, MAX_LINE))
        printf("\t%g\n", sum += atof(line));
    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10.0 + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

int get_line(char s[], int lim)
{
    int c, i = 0;
    while (--lim >= 0 && (c = getchar()) != EOF) {
        s[i++] = c;
        if(c == '\n')
            break;
    }
    s[i] = '0';
    return i;
}

