#include "std_lib.h"

#define ALLOC_SIZE 10000
static char allocbuf[ALLOC_SIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOC_SIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else 
    return 0;
}
void afree(char *p)
{
    if(p >= allocbuf && p <= allocbuf + ALLOC_SIZE)
        allocp = p;
}
