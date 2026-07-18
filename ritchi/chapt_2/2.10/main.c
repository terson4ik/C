#include <stdio.h>
#include "bits.h"

#define TARG_COUNT 1 + 1
int main(int argc, char **argv)
{
    unsigned int x;
    if (argc < TARG_COUNT)
        return 1;

    x = str_to_bin(argv[1]);

    printf("%d\n", bitcount(x));
    print_bits(x);
    return 0;
}
