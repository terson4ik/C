#include <stdio.h> /* for NULL*/
#include "alloc.h"

#define ALLOC_SIZE  10000

static char arr_alloc[ALLOC_SIZE];
static char *parr = arr_alloc;

char *alloc(unsigned int size)
{
    if ((arr_alloc + ALLOC_SIZE) - parr >= size) {
        parr += size;
        return parr - size;
    } else
        return NULL;
}

void afree(char *p)
{
    if (p >= arr_alloc && (p < (arr_alloc + ALLOC_SIZE)))
        parr = p;
}