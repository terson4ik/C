#include <stdio.h>

void str_cat(char s[], const char *t)
{
    int i, j;
    i = j = 0;
    while(s[i] != 0)
        i++;
    while((s[i++] = t[j++]) != '\0')
        ;
}

int main()
{
    char str[100] = "have a good day\n";
    str_cat(str, "ITS SECOND PART OF THIS SHIT\n");
    printf("%s", str);
    return 0;
}
