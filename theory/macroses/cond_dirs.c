#include <stdio.h>

#ifndef USE_INDEX_IN_STRING_COPY
#define USE_INDEX_IN_STRING_COPY    1
#endif
/* in cmd we do this: gcc -D USE_INDEX_IN_STRING_COPY=1 .......*/

/* for example, if can be used for hide anyone fragment of text */
/* if it needs, just change 0 to 1 */
#if 0 /* this implementation was too slow */
void sort(int *a, int n)
{
    /* ... */
}
#endif

/* type of integer in macro conditions is LONG!!! For example 
 * if MACROS is the same of the if 0L */
#if defined(DEBUG_PRINT) && DEBUG_PRINT > 7
#endif
/* ifdef = if defined; 
 * ifndef = if !defined;
*/
/* we can also do this */
#if USE_INDEX_IN_STRING_COPY
void string_copy(char *dest, const char *src)
{
    int i;
    for(i = 0; src[i]; i++)
        dest[i] = src[i];
    dest[i] = 0;
}
#else
void string_copy(char *dest, const char *src)
{
    for(; *src; dest++, src++)
        *dest = *src;
    *dest = 0;
}
#endif

#if defined(FOR_PETROV)
    /* code for Petrov */
#elif defined(FOR_SIDOROV)
    /* code for Sidorov */
#else
    /* code for other */
#endif

#define MY_MAC
/* in cmd we do this: gcc -D MY_MAC .......*/
int main(void)
{
    return 0;
}
