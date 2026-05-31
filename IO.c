#include <stdio.h>

int main()
{
    int c;
    while((c = getchar()) != EOF) {
        if(c == '\n')
            printf("[OK]\n");
    }
    return 0;
}
