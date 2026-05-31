#include <stdio.h>

int main()
{
    int c, i;
    i = 0;
    while((c = getchar()) != EOF) {
        if(c == '\n') {
            printf("%d\n", i);
            i = 0;
        } else {
        ++i;
        }
    }
    return 0;
}
