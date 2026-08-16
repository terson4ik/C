#include <stdio.h>
#include <string.h>

enum { MIN_PRINT = 32, MAX_LINE = 80, MAX_PRINT = 126 };

int main()
{
    int c, len;
    if (MAX_LINE < 0) /* safety macros */
        return 0;

    len = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            len = 0;
            putchar('\n');
            continue;
        } 
        if (c < MIN_PRINT || c > MAX_PRINT) {
            char buf[10];
            snprintf(buf, 10, "\\X%02X", c);
            if (len + strlen(buf) > MAX_LINE) {
                putchar('\n');
                len = 0;
            }
            len += printf("%s", buf);
        } else {
            len++;
            if (len > MAX_LINE) {
                putchar('\n');
                len = 1;
            }
            putchar(c);
        }
    }
    return 0;
}
