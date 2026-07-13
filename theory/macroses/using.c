#include <stdio.h>

/* NEVER USE THIS!!!
    #if
USE THIS
#  if
*/

#define MAX_ARRAY_FOR_BUBBLE 30
#ifdef FIXED_ARRAY_SIZE
    int array[ARRAY_SIZE];
#else
    int *array = malloc(sizeof(*array) * arrsize);
#endif
        /* ... */
#ifdef FIXED_ARRAY_SIZE
#  if ARRAY_SIZE > MAX_ARRAY_FOR_BUBBLE
    quick_sort_int(array, ARRAY_SIZE);
#  else
    bubble_sort_int(array, ARRAY_SIZE);
#  endif
#else
    if(arrsize > MAX_ARRAY_FOR_BUBBLE)
        quick_sort_int(array, ARRAY_SIZE);
    else
        bubble_sort_int(array, ARRAY_SIZE);
#endif

int main(void)
{
    int a = 5, b = 10;
    return 0;
}
