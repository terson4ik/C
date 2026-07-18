#include <stdio.h>
#include "bits.h"

#define BASE_10 10
u_64 a_to_i(const char *s);

#define TARG_N 3 + 1 /* +1 = ./prog */
int main(int argc, char **argv)
{
    u_64 x, p, n;
    if (argc < TARG_N) {
        fprintf(stderr, "FATAL ERROR: too few arguments");
        return 1;
    }
    x = a_to_i(argv[1]);
    p = a_to_i(argv[2]);
    n = a_to_i(argv[3]);
    print_bits(x);
    print_bits(getbits(x, p, n));
    return 0;
}

u_64 a_to_i(const char *s)
{
    u_64 res = 0;
    for (; *s != '\0'; s++)
        if(*s >= '0' && *s <= '9')
            res = (res * BASE_10) + (*s - '0');
        else {
            fprintf(stderr, "FATAL ERROR: char %c in atoi", *s);
            return 0;
        }

    return res;
}
