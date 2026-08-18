/* 7.4 -- miniscanf */
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

int miniscanf(const char *fmts, ...);

int main()
{
    char buf[4096];
    int x;
    fputs("Enter for example numer and string\n", stderr);

    miniscanf("%d %s", &x, buf);
    printf("%d, %s\n", x, buf);
    return 0;
}

int miniscanf(const char *fmts, ...)
{ /* very simple */
    const char *p = fmts;
    int success_vars = 0;
    va_list ap;

    va_start(ap, fmts);
    while (success_vars >= 0 && *p) {
        char fin_fmts[30];
        int i;
        if (isspace(*p)) {
            p++;
            continue;
        }

        fin_fmts[0] = *p++;
        for (i = 1; *p && !isalpha(*p) && *p != '%'; i++)
            fin_fmts[i] = *p++;
        fin_fmts[i++] = *p;
        fin_fmts[i] = '\0';

        switch(*p) {
            case 'c':
                if (scanf(fin_fmts, va_arg(ap, char *)) != 1) {
                    success_vars = -1;
                    goto end;
                }
                break;
            case 'i':
            case 'u':
            case 'x':
            case 'o':
            case 'd':
                if (scanf(fin_fmts, va_arg(ap, int *)) != 1) {
                    success_vars = -1;
                    goto end;
                }
                break;
            case 'e':
            case 'f':
            case 'g':
                if (scanf(fin_fmts, va_arg(ap, float *)) != 1) {
                    success_vars = -1;
                    goto end;
                }
                break;
            case 's':
                if (scanf(fin_fmts, va_arg(ap, char *)) != 1) {
                    success_vars = -1;
                    goto end;
                }
                break;
            case '\0':
                goto end;
            case '%':
                break;
            default:
                fprintf(stderr, "unknown specifier: %c", *p);
                success_vars = -1;
                break;
        }
        p++;
        success_vars++;
    }
end:
    va_end(ap);
    return success_vars;
}
