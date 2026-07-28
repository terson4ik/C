#include <stdio.h>

char *strcat(char *s, const char *t);
#define MAXLINE 30
int main() /* int argc, char **argv */
{
    char s[MAXLINE] = "hello";
    char *t = " world!\n";
    //fputs(strcat(s, t), stdout);
    printf("%s", strcat(s, t));
    return 0;
}

char *strcat(char *s, const char *t)
{
    char *save = s;
    while (*s)
        s++;
    while ((*s++ = *t++))
        ;
    return save;
}
