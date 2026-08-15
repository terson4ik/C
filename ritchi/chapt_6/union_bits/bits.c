#include <stdio.h>

/* see DEMKA after function main */
struct { /* this is bit fields */
    unsigned int is_keyword : 1; /* width in bits */
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
} flags_s;

int main(void)
{
    /* set on EXTERNAL and STATIC */
    flags_s.is_extern = flags_s.is_static = 1;
    /* remove EXTERNAL and STATIC */
    flags_s.is_extern = flags_s.is_static = 0;
    /* true if EXTERNAL and STATIC power off */
    if (flags_s.is_extern == 0 && flags_s.is_static == 0)
        ;
/* эти поля системно-зависимы, и каждой реализации само решаетс, могут ли поля
 * перекрывать границы слов(залезть с первого байта на второй).
 * также эти битовые поля не обязаны иметь имена, можно просто двоеточие. 
 * также для принудительного выравнивания по границе след. слова можно использовать
 * спец знач равное 0. совокупность полей не массив, поэтому применять взятие адрессов
 * нельзя. надо ещё учитывать биг ендиан или литл ендиан, также АНСИ требует инт для полей
 * лучше ставить беззнаковый.

    return 0;
}
/* DEMKA */
/* #define KEYWORD  01
   #define EXTERNAL 02
   #define STATIC   04 */
/* Recommended like this: */
enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 }; /* must be a power of two */
void demka(void)
{
    int flags
    /* set on EXTERNAL and STATIC */
    flags |= EXTERNAL | STATIC; /* 0011 */
    /* remove EXTERNAL and STATIC */
    flags &= ~(EXTERNAL | STATIC); /* ~(0011)= 1100 */

    /* true if EXTERNAL and STATIC power off */
    if (flags & (EXTERNAL | STATIC) == 0)
        putchar(' ');
}
