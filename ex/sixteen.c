#include <stdio.h>

#define MAXLEN  3

int getsize();
int get_line(char str[], int limit);
void copy(char *dest, const char *src);

int main()
{
    int max, length;
    char tmp_arr[MAXLEN];
    char max_arr[MAXLEN];

    max = 0;
    while((length = get_line(tmp_arr, MAXLEN)) != 0) {
        if(tmp_arr[length - 1] != '\n') 
            length += getsize();
        if(max < length) {
            max = length;
            copy(max_arr, tmp_arr);
        }
    }
    printf("%d\n", max);
    printf("%s", max_arr);
    if(max > MAXLEN)
        putchar('\n');
    return 0;
}

int getsize()
{
    int c, res;
    for(res = 0; (c = getchar()) !=EOF && c != '\n'; ++res)
    {}
    if(c == '\n')
        ++res;
    return res;
}

int get_line(char str[], int limit)
{
    int c, i;
    if(!limit)
        return 0;

    for(i = 0; i < limit-1 && ((c = getchar()) != EOF && c != '\n'); ++i)
        str[i] = c;

    if(c == '\n' && i < limit - 1) {
        str[i] = '\n'; /* in while '\n' will be skip */
        ++i;    /* new symbol was added */
    }
    str[i] = '\0';
    return i;
}

void copy(char *dest, const char *src)
{
    int i;
    for(i = 0; (dest[i] = src[i]); ++i)
    {}
}
