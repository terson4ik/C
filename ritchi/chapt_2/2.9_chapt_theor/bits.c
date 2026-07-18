#include <stdio.h>
#include <limits.h>
#include "bits.h"

#define NL  putchar('\n')
void print_n_bits(u_64 x, u_64 p, u_64 n)
{
    u_64 i;

    for (i = 1; n >= i; i++)
/* Position p starts with 0, then p = p+1; For example x = 1010, p = 2, n = 3
 * ->010 p+1 = 3, 3 - 1 = 2, 010 >> 2 = 0 & 1; 3 - 2 = 1, 010 >> 1 = 01 & 1 */
        printf("%lld", (x >> (p + 1 - i)) & 01);
    NL;
}

void print_bits(u_64 x)
{
    int i;
    for (i = UINT_WIDTH; i >= 0; i--)
        printf("%lld", (x >> i) & 01);
    NL;
}

u_64 getbits(u_64 x, u_64 p, u_64 n)
{
    /* Give 1010, p = 3, n = 2; p starts with 0, then p = p + 1, because 
     * if p = 0 and n = 1 then have error. Next need to shift:
     * from 3(4) position need 2 bits. It's (p + 1 - n) shift to right
     * ->1010 >> p+1-n=3+1-2 = 1010 >> 2 = 0010; next need the mast
     * to dispose all left bits, this ~(~0 << n):
     * ~(1111 << 2) = ~(1100) = 0011; and use & to 0010 and return it */
    return (x >> (p + 1 - n)) & ~(~0 << n);
}
