#include <stdio.h>
#include <string.h>


char *reverse(char s[])
{
    int i, j, c;
    
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) 
        c = s[i], s[i] = s[j], s[j] = c;
/*
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
*/
    return s;
}

int main(int argc, char **argv)
{
    char str[4096];
    if (argc < 2)
        return 1;
    strcpy(str, argv[1]);
    printf("%s\n", reverse(str));
    return 0;
}
