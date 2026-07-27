#include <stdio.h>

#define swap(t, x, y) { t tmp = x; x = y; y = tmp; }
int main()
{
    int a = 5;
    int b = 10;

    printf("%d\t%d\n", a, b);
    swap(int, a, b);
    printf("%d\t%d\n", a, b);
    return 0;
}
