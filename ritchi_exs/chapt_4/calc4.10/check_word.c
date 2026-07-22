#include "check_word.h"
#include "getop.h"
#include "my_string.h"

int check_word(char s[])
{
    if (cmp_str(s, "sin"))
        return SIN;
    else if (cmp_str(s, "cos"))
        return COS;
    else if (cmp_str(s, "exp"))
        return EXP;
    else if (cmp_str(s, "sqrt"))
        return SQRT;
    else if (cmp_str(s, "pow"))
        return POW;
    else if (cmp_str(s, "swap"))
        return SWAP;
    else if (cmp_str(s, "dubl"))
        return DUBL;
    else if (cmp_str(s, "print"))
        return PRINT;
    else if (cmp_str(s, "clear"))
        return CLEAR;
    else
        return ERR_OP;
}
