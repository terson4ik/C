#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "getop.h"
#include "stack.h"

#define HELP_MSG \
"Available next features:\n"\
"PRINT\n" \
"DUBL \n" \
"SWAP \n" \
"CLEAR\n" \
"SIN  \n" \
"COS  \n" \
"EXP  \n" \
"SQRT \n" \
"POW  \n" \
"And variables, by default all vars equal 0; try it: `1 a =`\n" \
"Also have var '_' -- save the last output number.\n"

#define MAX_OP  100
#define LETTERS 26 + 26 + 1 /* +1 support var */
#define UNKOWN_VAR -1
enum var_states { NO, READY_TO_PRINT, YES };

int main()
{
    char s[MAX_OP];
    double vars[LETTERS] = { 0.0 };
    double op2;
    int type, last_var;
    enum var_states is_eq;

    vars[LETTERS-1] = NAN;
    last_var = UNKOWN_VAR;
    is_eq = NO;
    fputs(HELP_MSG, stderr);
    while((type = get_op(s)) != EOF) {
        if (is_eq != NO) {
            if (is_eq == YES)
                is_eq = READY_TO_PRINT;
            else if (is_eq == READY_TO_PRINT) {
                is_eq = NO;
                last_var = UNKOWN_VAR;
            }
        }
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case PRINT:
                print_top();
                break;
            case DUBL:
                dublic_top();
                break;
            case SWAP:
                swap_s();
                break;
            case CLEAR:
                clear_s();
                break;
            case SIN:
                push(sin(pop() * M_PI / 180));
                break;
            case COS:
                push(cos(pop() * M_PI / 180));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case SQRT:
                op2 = pop();
                if (op2 < 0)
                    fprintf(stderr, "SQRT of x < 0. \n");
                else
                    push(sqrt(op2));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case VAR_OP:
                if (s[0] == LAST_VR)
                    last_var = LETTERS - 1;
                else
                    last_var = (s[0] >= 'A' && s[0] <= 'Z') ? s[0] - 'A'+ 26
                                                             : s[0] - 'a';
                push(vars[last_var]);
                break;
            case '=':
                pop(); /* after var_op is not arithmetic action */
                if(last_var == UNKOWN_VAR) {
                    fprintf(stderr, "Fatal error: no variable specified\n"
                                     "Erased all data...\n");
                    clear_s();
                } else {
                    vars[last_var] = pop();
                    is_eq = YES;
                }
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 == 0)
                    fprintf(stderr, "DIVIDED BY ZERO. WTF?\n");
                else
                    push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                if (op2 == 0)
                    fprintf(stderr, "MOD BY ZERO. WTF?\n");
                else
                    push((int) (pop()) % (int) (op2));
                break;
            case '\n':
                if(is_eq == READY_TO_PRINT && last_var != UNKOWN_VAR) {
                    printf("var %c = %.8g\n", (last_var > 25) ?
                        last_var -26+'A' : last_var + 'a', vars[last_var]);
                    last_var = UNKOWN_VAR;
                } else {
                    printf("\t%.8g\n", (vars[LETTERS-1] = pop()));
                }
                break;
            case ERR_OP:
            default:
                fprintf(stderr, "Incorrect operator/operand: %s\n", s);
                break;
        }
    }
    return 0;
}
