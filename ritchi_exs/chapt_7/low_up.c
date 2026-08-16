#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int c;
    int (*to_registr)(int );
    for (c = 0; argv[0][c] != '\0' && !isalpha(argv[0][c]); c++)
        ;
    if (argv[0][c] == '\0') {
        fprintf(stderr, "%s: no detected ASCII a-z or A-Z chars", argv[0]);
        return 1;
    }
    to_registr = islower(argv[0][c]) ? tolower : toupper;
    while ((c = getchar()) != EOF)
        putchar(to_registr(c));
    return 0;
}
