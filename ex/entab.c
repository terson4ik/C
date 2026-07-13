/* remove n-spaces and print tabs */
#include <stdio.h>

#define TAB_SIZE    8

int main()
{
    int c;
    char size, column;

    column = size = 0;
    while((c = getchar()) != EOF) {
        ++column;
        if(c == ' ') {
            ++size;
            if(column == TAB_SIZE) {
                putchar('\t');
                size = 0;
            }
        } else {
            for(; size; --size)
                putchar(' ');
            putchar(c);
        }
        if(column == TAB_SIZE || c == '\n' || c == '\t')
            column = 0;
    }

    return 0;
}
