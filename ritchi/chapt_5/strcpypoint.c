#include <stdio.h>

void str_cpy_realy_good(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

void str_cpy_good(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
}
void str_cpy(char *s, char *t)
{
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

int main() /* int argc, char **argv */
{
    return 0;
}
