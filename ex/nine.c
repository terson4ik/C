#include <stdio.h>

int main()
{
    int c, is_space;
    is_space = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            if(is_space == 0) {
                ++is_space;
                putchar(c);
            } else {
                continue;
            }
        } else {
            is_space = 0;
            putchar(c);
        }
    }
    return 0;
}
