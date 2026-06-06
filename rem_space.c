#include <stdio.h>

void rem_char(char *str, const char c)
{
    int i, j;
    for(i = j = 0; str[j]; j++) {
        if(str[j] != c) {
            str[i] = str[j];
            ++i;
        }
    }
    str[i] = 0;
}

int main()
{
    char str[] = "h e l l o w o r l d";

    rem_char(str, ' ');
    printf("%s\n", str);

    return 0;
}
