#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main()
{
    minprintf("%d %f %s", 123, 5.5, "Hello, world!\n");
    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p;
    union {
        char cval;
        int ival;
        double dval;
        char *strval;
        void *ptrval;
    } form;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'c':
                form.cval = va_arg(ap, int); /* char not supported in this macros */
                putchar(form.cval);
                break;
            case 'i':
            case 'd':
                form.ival = va_arg(ap, int);
                printf("%d", form.ival);
                break;
            case 'u':
                form.ival = va_arg(ap, int);
                printf("%u", (unsigned) form.ival);
                break;
            case 'f':
                form.dval = va_arg(ap, double);
                printf("%f", form.dval);
                break;
            case 'G':
                form.dval = va_arg(ap, double);
                printf("%G", form.dval);
                break;
            case 'g':
                form.dval = va_arg(ap, double);
                printf("%g", form.dval);
                break;
            case 's':
                for (form.strval = va_arg(ap, char *); *form.strval; form.strval++)
                    putchar(*form.strval);
                break;
            case 'p':
                form.ptrval = va_arg(ap, void *);
                printf("%p", form.ptrval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
