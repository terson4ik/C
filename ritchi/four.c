#include <stdio.h>

/* print table of C* -> F* degrees */
int main()
{
    float celc, farh;
    int lower, upper, step;
    lower = -50;
    upper = 300;
    step = 10;
    celc = lower;
    while(celc <= upper) {
        farh = (celc * 9.0/5.0) + 32;
        printf("%-6.0f %6.2f\n", celc, farh);
        celc += step;
    }
    return 0;
}
