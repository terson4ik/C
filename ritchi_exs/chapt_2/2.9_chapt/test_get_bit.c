#include <stdio.h>
#include "bits.h"
#include "a_to_i.h"

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
