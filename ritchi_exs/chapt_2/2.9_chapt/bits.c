#include <stdio.h>
#include <limits.h> /* Width to ULONG is too long */
#include "bits.h"
#define BYTE_SIZE 8
u_64 custom_sizeof(void)
{
    u_64 i;
    u_64 n;
    for (i = 0, n = ~0ULL; n; i++)
        n >>= 1;
    return i / BYTE_SIZE;
}

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
    for (i = custom_sizeof() * BYTE_SIZE; i >= 0; i--)
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

u_64 setbits(u_64 x, u_64 p, u_64 n, u_64 y)
{
/* Give x=1000, p=3, n=3, y=1111 */
    return
/* Make hole from X: from position p+1
 * (because n started with 1, p started with 0)
 * ~(~0 << n)= 1111 << 3 = ~1000=0111; and shift to p+1-n=1
 * 01110= ~01110=10001; use & to x:         */
        (x & (~(~(~0ULL << n) << (p + 1 - n))))
    | /* Glue hole and new value in mask */
/* Make template from Y: need 3 LEFTS bites:
 * ~(~0 << n) = 00111; next shift to p+1-n: */
        (y & (~(~0ULL << n))) << (p + 1 - n);
/* It's need to return */
}
u_64 invert(u_64 x, u_64 p, u_64 n)
/* XOR:
 * 1 ^ 1 = 0 negative
 * 0 ^ 1 = 1 negative
 * 1 ^ 0 = 1 saved
 * 0 ^ 0 = 0 saved
 * it's local ~ */
{
/* Use ^: build mask: ~(~(~0 << n) << p + 1 - n)
 * and just use ^: */
    return x ^ (~(~0ULL << n) << (p + 1 - n));
}

u_64 rightrot(u_64 x, u_64 n)
{
#if 1
/* 0011 >> 2; 4 - 2; 11 << 2 = 1100 */
    return (x >> n) | (x << ((custom_sizeof() * BYTE_SIZE) - n));
#else
    int i;
    for (i = n; i; --i)
        if ((x & 01) == 1) {
            x >>= 1;
            x |= ~(~0UUL >> 1);
        }
        else
            x >>= 1;
    return x;
#endif
}
