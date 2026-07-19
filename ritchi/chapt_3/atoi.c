#include <stdio.h>

#include <ctype.h>

int atoi(const char s[]);
int main(int argc, char **argv)
{
    if(argc < 2)
        return 1;

    
    printf("%d\n", atoi(argv[1]));
    return 0;
}

int atoi(const char s[])
{
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for(n = 0; isdigit(s[i]); i++) 
        n = 10 * n + (s[i] - '0');
    return sign * n;
}
