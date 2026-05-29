#include <stdio.h>

int put_sum(int *a, int *b, int *c) {
    int temp;
    temp = *a + *b + *c;
    *a = *b = *c = temp;
    return temp;
}

int main() {
    int x, y, z;
    x = y = z = 10;
    printf("%d, %d, %d\n", x, y, z);
    printf("x = %d, func = %d, x = %d\n", x, put_sum(&x, &y, &z), x);
    printf("%d, %d, %d\n", x, y, z);
    return 0;
}
