#include <stdio.h>
#include "print_bits.h"

unsigned int getbits(unsigned int x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main()
{
    int x, diag;
    diag = scanf("%d", &x);
    if(diag != 1)
        return 1;
    print_bits(x);
    print_bits(getbits(x, 4, 3));
    return 0;
}
