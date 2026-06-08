#include <stdio.h>

#define BUF_SIZE    1024    /* 1 kb is ok; in future need malloc + realoc*/

int read_seq(char buffer[], int limit);
void rm_space_tail(char str[], int end);

int main()
{
    int length;
    char buf[BUF_SIZE];
    while((length = (read_seq(buf, BUF_SIZE)))) {
        rm_space_tail(buf, length - 1); /* common offset for arr */
        if(buf[0] != '\n')
            printf("%s", buf);
    }
    return 0;
}

int read_seq(char str[], int lim)
{
    int c, i;
    for(i = 0; i<lim && (c = getchar()) !=EOF; ++i) {
        str[i] = c;
        if(c == '\n') {
            ++i;
            break;
        }
    }
    str[i] = '\0';
    return i;
}

void rm_space_tail(char str[], int end)
{
    int i, c;
    for(i = end; i >= 0; --i) {
        c = str[i];
        /* if found not space char */
        if(c != ' ' && c != '\t' && c != '\n') {
            str[i + 1] = '\n';
            str[i + 2] = '\0';
            return;
        }
    }   
    if(i < 0) {
        str[0] = '\n';
        str[1] = '\0';
    }
}
