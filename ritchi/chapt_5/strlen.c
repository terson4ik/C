#include <stdio.h>

int strlen(const char *s);

int main() /* int argc, char **argv */
{
    char *s = "hello\n";
    printf("%d\n", strlen(s));
    return 0;
}

int strlen(const char *s)
{
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}
