#include <stdio.h>
#include <stdarg.h>

int sum(int c, ...)
{
    va_list vl;
    int s = c, k;
    
    va_start(vl, c);
    while ((k = va_arg(vl, int)) != 0)
        s += k;
    va_end(vl);
    return s;
}

void print_times(const char *str, ...)
{
    va_list vl;
    const char *p;

    va_start(vl, str);
    for (p = str; p; p = va_arg(vl, const char *)) {
        int n;
        for (n = va_arg(vl, int); n > 0; n--)
            printf("%s ", p);
        putchar('\n');
    }
    va_end(vl);
}

int main()
{
    printf("sum: %d\n", sum(5, 10, 8, 0));
    print_times("once", 1, "twice", 2, "seven times", 7, NULL);
    return 0;
}
