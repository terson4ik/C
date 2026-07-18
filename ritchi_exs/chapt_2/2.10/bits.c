#include <stdio.h>
#include "bits.h"

#define BASE_BIN 2

unsigned int bitcount(unsigned int x)
{
/* 101 = 100 & 101 = 100;
 * 1010 = 1001 & 1010 = 1000; 1000 - 1 = 0111 & 1000 = 1;..... */
    int b;
/* x &= x - 1 is equal x = x & (x - 1) */
    for (b = 0; x != 0; x &= x - 1)
        b++;
    return b;
}

unsigned int str_to_bin(const char *str)
{
    char c;
    unsigned int res;

    for (res = 0; (c = *str) != '\0'; str++)
        if (c >= '0' && c <= '1')
            res = (res * BASE_BIN) + (c - '0');
        else
            return 0;

    return res;
}

void print_bits(unsigned int x)
{
    int i;

    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
        printf("%u", (x >> i) & 01);
    putchar('\n');
}
