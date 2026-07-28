#include <stdio.h>

void str_cpy(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

int main() /* int argc, char **argv */
{
    return 0;
}
