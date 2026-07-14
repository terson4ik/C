#include <stdio.h>

int atoi(const char s[])
{
    int i, n;

    n = 0;
    for(i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = n * 10 + s[i] - '0';
    return n;
}
int main()
{
    return 0;
}
