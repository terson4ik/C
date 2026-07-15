#include <stdio.h>

void squeeze(char s[], int c)
{
    int i, j;
    for (i = j = 0; s[i]; i++)
        if(s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

int main()
{
    char str[] = "!!!!!!!!!have!!!! a!!!!!! good!!! day!!!!!!!!\n";
    squeeze(str, '!');
    printf("%s", str);
    return 0;
}
