#include <stdio.h>
#include <stdlib.h>
#include "rand.h"

int main(int argc, char **argv)
{
    int i;
    if(argc < 2)
        return 0;
    /* Need a current time in OS */
    srand(1000);
    i = atoi(argv[1]);
    while(i--)
        printf("%d\n", rand());
    return 0;
}
