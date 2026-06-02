#include <stdio.h>

int main()
{
    int c, spaces, tabs, nl;
    spaces = tabs = nl = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            ++spaces;
            continue;
        }
        if(c == '\t') {
            ++tabs;
            continue;
        }
        if(c == '\n') {
            ++nl;
            continue;
        }
    }
    printf("spaces:    %5d\n", spaces);
    printf("tabs:      %5d\n", tabs);
    printf("new lines: %5d\n", nl);
    return 0;
}
