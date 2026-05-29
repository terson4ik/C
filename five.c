#include <stdio.h>

int get_and_zero(int *decimal) {
    int t = *decimal;
    *decimal = 0;
    return t;
}

int main() {
    int a = 10;
    int x = 301;
    printf("a = %d, x = %d\n", a, x);
    x = get_and_zero(&a);
    printf("a = %d, x = %d\n", a, x);
    return 0;
}
