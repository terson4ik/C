#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HELP_MSG "Example of use: \"./prog 20 word\".\n"
#define ERR_MSG "Count is negative.\n"

int main(int argc, char **argv)
{
    size_t i;
    if(argc < 3) {
        fprintf(stderr, HELP_MSG);
        return 1;
    }

#ifdef MAX_HARD
    i = ULLONG_MAX;
#else
    if(*(argv[1]) == '-') {
        fprintf(stderr, ERR_MSG);
        return 2;
    }
    i = atoi(argv[1]);
#endif

    for(; i; --i) {
#ifndef NL_TYPE
        printf("%s ", argv[2]);
    }
    putchar('\n');
#else
        printf("%s \n", argv[2]);
    }
#endif

    return 0;
}
