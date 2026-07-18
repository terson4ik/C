#include <stdio.h>
#include "a_to_i.h"
#include "bits.h" /* for u_64 */
#define BASE_10 10
u_64 a_to_i(const char *s)
{
    u_64 res = 0;
    for (; *s != '\0'; s++)
        if(*s >= '0' && *s <= '9')
            res = (res * BASE_10) + (*s - '0');
        else {
            fprintf(stderr, "FATAL ERROR: char %c in atoi", *s);
            return 0;
        }

    return res;
}
