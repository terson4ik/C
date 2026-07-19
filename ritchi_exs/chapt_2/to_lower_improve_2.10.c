#include <stdio.h>

char lower(char c);

int main()
{
    char str[] = "THIS IS a very BIG problem LOLAAAAA.!!!!$$$$##$%*))*^\n";
    int i;
    printf("%s", str);
    for (i = 0; str[i] != '\0'; i++)
        putchar(lower(str[i]));
    return 0;
}

char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
