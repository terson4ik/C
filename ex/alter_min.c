#include <stdio.h>

#define MAXLEN  1000

int  get_length();
int  get_line(char str[], int limit);
void copy(char *dest, const char *src);

/* finding MINIMUM length string and print them */
int main()
{
    unsigned int min, cur;
    char tmp[MAXLEN];
    char min_str[MAXLEN];

    min = -1;
    while((cur = get_line(tmp, MAXLEN)) != 0) {
        if(cur == MAXLEN)
            cur += get_length();

        if(min > cur) {
            min = cur;
            copy(min_str, tmp);
        }
    }

    printf("%s", min_str);
    return 0;
}

int get_length()
{
    int res, c;

    res = 0;
    while((c = getchar()) != EOF && c != '\n')
        ++res;

    if(c == '\n')
        ++res;
    return res;
}

int get_line(char str[], int limit)
{
    int c, i;

    for(i = 0; ((c = getchar()) !=EOF && c != '\n') && limit - i; ++i)
        str[i] = c;

    /* if '\n' then element [I] don't write this symbol */
    if(c == '\n') {
        str[i] = '\n'; /* literal always faster then memory access */
        ++i;    /* add this new char to counter */
    }
    str[i] = '\0';
    return i;
}

    
/* copy strings */
void copy(char *dest, const char *src)
{
    int i;
    for(i = 0; (dest[i] = src[i]); ++i)
    {}
}
