#include <stdio.h>
#include <stdlib.h>

#define frand() ((double) rand() / (RAND_MAX+1.0))
int main()
{
    int i = 7;
    while (i-- > 0)
        printf("%g\n", frand());
    return 0;
}
