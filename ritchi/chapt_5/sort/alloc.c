#include <stdio.h> /* for NULL */
#include "alloc.h"

#define ALLOC_SIZE  10000
static char alloc_buf[ALLOC_SIZE];
static char *alloc_ptr = alloc_buf;

char *alloc(int size)
{
    if (alloc_buf + ALLOC_SIZE - alloc_ptr >= size) {
        alloc_ptr += size;
        return alloc_ptr - size;
    } else
        return NULL;
}

void afree(char *ptr)
{
    if (ptr >= alloc_buf && ptr < alloc_buf + ALLOC_SIZE)
        alloc_ptr = ptr;
}
