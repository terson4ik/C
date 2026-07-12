#include <stdio.h>

#define HELLOMSG    "Hello world\n"
#undef HELLOMSG

#if !defined(FOR_PETROV) && !defined(FOR_SIDOROV)
#error Please define either FOR_PETROV or FOR_SIDOROV
#endif

#ifndef BUFFER_SIZE
#error Please specify the buffer size
#endif

/* for another languages who is result of text in C use directive #line */
/* we have specific MACROCHARS and nothing do:
 * __LINE__ - current line(integer const)
 * __FILE__ - current processing file name(strings literal)
 * __DATE__ - current date(strings literal)
 * __TIME__ - current time(strings literal)
 * __STDC__ - always equal 1. показывает соответсвует ли компилятор стандарту */
int main(void)
{
    int a = 5, b = 10;

    return 0;
}
