#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
int get_line(char s[], int lim);

#define MAX_LINE 1000
int main()
{
    char line[MAX_LINE];

    double sum = 0.0;
    while (get_line(line, MAX_LINE))
        printf("\t%g\n", sum += atof(line));
    return 0;
}

int is_sign(char c)
{
    return c == '-' || c == '+';
}

double atof(char s[])
{
    double val, power, expn;
    int sign, expn_sign, i, expn_base;
    
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (is_sign(s[i]))
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10.0 + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'E' || s[i] == 'e') {
        i++;
        expn_sign = (s[i] == '-') ? -1 : 1;
        if (is_sign(s[i]))
            i++;
#ifdef DANGER
        expn_base = (int) atof(s + i);
#else
        for (expn_base = 0; isdigit(s[i]); i++)
            expn_base = expn_base * 10 + (s[i] - '0');
#endif
        for (expn = 1.0; expn_base > 0; expn_base--)
            expn *= 10.0;
        power = (expn_sign < 0) ? power * expn : power / expn;
    }
    return val * sign / power;
}

int get_line(char s[], int lim)
{
    int c, i = 0;

    while (--lim > 0 && (c = getchar()) != EOF) {
        s[i++] = c;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}
