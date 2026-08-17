#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main()
{
    minprintf("%d %f %s", 123, 5.5, "Hello, world!\n");
    return 0;
}

void minprintf(char *fmt, ...)
{
    char ready_fmt[20];
    va_list ap;
    char *p;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        int idh;
        if (*p != '%') { /* default char */
            putchar(*p);
            continue;
        }
        /* filling format string for true printf 
         * anyone modifier is alphabet symbol */
        idh = 0;
        ready_fmt[idh++] = *p++;
        /* -2 because LETTER + 0 */
        while (*p && !isalpha(*p) && *p != '%' && idh < sizeof(ready_fmt) -2)
            ready_fmt[idh++] = *p++;

        ready_fmt[idh++] = *p; /* enter modifier */
        ready_fmt[idh] = '\0';
        switch (*p) {
            case 'c':
            case 'i':
            case 'x':
            case 'X':
            case 'd':
            case 'u':
                printf(ready_fmt, va_arg(ap, int));
                break;
            case 'f':
            case 'G':
            case 'g':
                printf(ready_fmt, va_arg(ap, double));
                break;
            case 's':
                printf(ready_fmt, va_arg(ap, char *));
                break;
            case 'p':
                printf(ready_fmt, va_arg(ap, void *));
                break;
            case '\0':
                return;
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
