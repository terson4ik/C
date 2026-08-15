#include <stdio.h>

#define NSYM 20
/* Объеденения это как структуры, но каждый елемент имеет отсуп от начала равное нулю,
 * сама она имеет достаточную длину для вмещения макс. елемента, а за выравнивание можно не беспокоиться
 * можно делать всё тоже самое что и со структурами.
 * не ясно, как сейчас, но АНСИ гласит что инициализоровать можно типом первого поля объеденения,
 * например тут можно инициализовать только интами */

struct {
    char *name;
    int flags;
    enum utypes { INT, FLOAT, STRING } utype;
    union {
        int ival;
        float fval;
        char *sval;
    } u;
} symtab[NSYM];

void demka(int ind);

int main(void)
{
    symtab[0].utype = INT;
    symtab[0].u.ival = 10;
    demka(0);

    symtab[1].utype = FLOAT;
    symtab[1].u.fval = 5.6;
    demka(1);

    symtab[2].utype = STRING;
    symtab[2].u.sval = "Hello, world!";
    demka(2);
    return 0;
}
void demka(int ind)
{
    if (symtab[ind].utype == INT)
        printf("%d\n", symtab[ind].u.ival);
    else if (symtab[ind].utype == FLOAT)
        printf("%f\n", symtab[ind].u.fval);
    else if (symtab[ind].utype == STRING) {
        printf("%s\n", symtab[ind].u.sval);
        printf("%c\n", symtab[ind].u.sval[0]);
        printf("%c\n", *symtab[ind].u.sval);
    } else
        printf("bat type %d in utype\n", symtab[ind].utype);
}
