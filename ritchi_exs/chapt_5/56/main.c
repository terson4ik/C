#include <stdio.h>
#include "other.h"
#include "getop.h"

#define MAXLINE 1000
int main() /* int argc, char **argv */
{
    char line[MAXLINE];
    int len;

    while ((len = getop(line)) != EOF) {
        switch (len) {
            case NUMBER:
                puts(line);
                break;
            default:
                putchar(len);
                break;
        }
    }
    return 0;
}
