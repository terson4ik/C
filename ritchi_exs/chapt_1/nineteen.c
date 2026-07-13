/* translate to Arabian */
#include <stdio.h>

#define MAXLEN  1024

void reverse(char s[]);
int  get_line(char buffer[], int limit);

int main()
{
    char buf[MAXLEN];
    while(get_line(buf, MAXLEN)) {
        reverse(buf);
        printf("%s", buf);
    }
    
    return 0;
}

void reverse(char s[])
{
    int i, j, tmp;
    for(j = 0; (tmp = s[j]) && tmp != '\n'; ++j)
        ;
    for(--j, i = 0; i < j; ++i, --j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}
int  get_line(char str[], int lim)
{
    int i, c;
    for(i = 0; i<lim && (c = getchar()) != EOF; ++i) {
        str[i] = c;
        if(c == '\n') {
            ++i;
            break;
        }
    }
    str[i] = '\0';
    return i;
}
