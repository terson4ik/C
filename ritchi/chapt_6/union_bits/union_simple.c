#include <stdio.h>

enum types {
    INT, FLOAT, STRING
} utype;
union u_tag {
    int ival;
    float fval;
    char *sval;
} u;
void demka(void);

int main(void)
{
    u.ival = 5;
    utype = INT;
    demka();

    u.fval = 5.6;
    utype = FLOAT;
    demka();

    u.sval = "Hello world\n";
    utype = STRING;
    demka();
    return 0;
}
void demka(void)
{
    if (utype == INT)
        printf("%d\n", u.ival);
    else if (utype == FLOAT)
        printf("%f\n", u.fval);
    else if (utype == STRING)
        printf("%s\n", u.sval);
    else
        printf("bat type %d in utype\n", utype);
}
