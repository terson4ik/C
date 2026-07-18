#include <stdio.h>
#include "bits.h"

#define BASE_BIN 2

unsigned int bitcount(unsigned int x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
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
