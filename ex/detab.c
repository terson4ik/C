#include <stdio.h>

#define TAB_SIZE    8

int main()
{
    int c;
    char size = 0;
    while((c = getchar()) != EOF) {
        if(c == '\t') {
            int i;
            for(i = 1; i <= TAB_SIZE - size; ++i)
            /* or use printf BUT size from tab need configure manually */
                putchar(' ');
            size = 0;
        } else {
            ++size;
            putchar(c);
        }
        if(size == TAB_SIZE || c == '\n')
            size = 0;
    }
}
