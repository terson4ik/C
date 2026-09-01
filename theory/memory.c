#include <stdlib.h>

calloc(int nmemb, int size) = malloc(nmemb * size)
but calloc filling all area of zeroes;

realloc(NULL, 5) == malloc;
realloc(valid, 0) == free;
