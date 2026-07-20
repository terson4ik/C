#include <stdio.h>
#include <string.h>

int trim (char s[])
{
    int n;
    
    for (n = strlen(s) - 1; n >= 0; n--)
        if(s[n] != ' ' && s[n] != '\n' && s[n] != '\t')
            break;
    s[++n] = '\0';
    return n;
}

int main()
{
    char s[1000];
    while(fgets(s, 1000, stdin)) {
        int n;
        printf("%ld: %s", strlen(s), s);
        n = trim(s);
        printf("%ld and %d: %s\n", strlen(s), n, s);
    }
    return 0;
}
