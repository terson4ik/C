#include <stdio.h>

#define MAX_LEN 2

#define IN      1
#define OUT     0

int is_space(char c)
{
    return c == ' ' || c == '\n' || c == '\t';
}

int main()
{
    int c, cur_len, state;
    char word[MAX_LEN + 1];

    /* default C string */
    word[MAX_LEN] = 0;
    state = OUT;
    cur_len = 0;

    while((c = getchar()) != EOF) {
        if(state == OUT && !is_space(c)) {
            state = IN;
            cur_len = 1;
            word[0] = c;
        } else if(state == IN && !is_space(c)) {
            ++cur_len;
            if(cur_len <= MAX_LEN) {
                word[cur_len - 1] = c;
            } else {
                cur_len = MAX_LEN + 1;
            }
        } else if((cur_len > 0 || c == '\n') && is_space(c)) {
            if(cur_len == MAX_LEN) {
                printf("%s", word);
                if(c != '\n')
                    putchar(c);
            }
            cur_len = 0;
            state = OUT;
            if(c == '\n')
                putchar('\n');
        }
    } 
    if(state == IN) {
        if(cur_len == MAX_LEN)
            printf("%s\n", word);
    }

    return 0;
}
