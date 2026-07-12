#include <stdio.h>

#define HELLOMSG    "Hello world\n"     /* it's 'macro-name'(макроимя) or
                                           just  'macros'(макрос) */

#define IF  if(
#define THEN ) {
#define ELSE } else {
#define FI  }

/* in the macro processor position, non capital identifies is legal
 *                                              for example, If iF or then*/
int main(void)
{
    int a = 5, b = 10;
    IF a > b THEN
        printf("the first was greater then the second\n");
        b = a;
    ELSE
        printf("the second was greater or equal\n");
        a = b;
    FI

    printf(HELLOMSG);   /* it's 'macro call'(макровызов) */
    return 0;
}
