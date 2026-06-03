#include <stdio.h>

#define INWORD  1
#define OUTWORD 0

int main()
{
    int c, state;

    state = OUTWORD;
    while((c = getchar()) != EOF) {
        if(state == OUTWORD && (c != ' ' && c != '\n' && c != '\t')) {
            putchar('(');
            state = INWORD;
        } else if(state == INWORD && (c == ' ' || c == '\n' || c == '\t')) {
            putchar(')');
            state = OUTWORD;
        }
        putchar(c);
    }

    if(state == INWORD) {
        putchar(')');
        putchar('\n');
    }

    return 0;
}
