#include <stdio.h>
#include "stack.h"

#define MAX_VAL         100
#define ERR_MSG_EMPT_ST "stack is empty\n"

static double val[MAX_VAL];
static int stack_p = 0;

void push(double x)
{
    if (stack_p < MAX_VAL)
        val[stack_p++] = x;
    else
        fprintf(stderr, "push: overflow stack.\n");
}

double pop(void)
{
    if (stack_p > 0)
        return val[--stack_p];
    else {
        fprintf(stderr, "pop:" ERR_MSG_EMPT_ST);
        return 0.0;
    }
}

void print_top()
{
    if (stack_p > 0)
        printf("CURRENT TOP: %.08g\n", val[stack_p - 1]);
    else
        fprintf(stderr, "print_top:" ERR_MSG_EMPT_ST);
}

double dublic_top()
{
    if (stack_p > 0) {
        push(val[stack_p-1]);
        return val[stack_p-1];
    } else {
        fprintf(stderr, "dublic_top:" ERR_MSG_EMPT_ST);
        return 0.0;
    }
}

void swap_s()
{
    if (stack_p < 2) {
        fprintf(stderr, "Too few elements. Ignored\n");
        return;
    }
    double tmp1 = pop();
    double tmp2 = pop();
    push(tmp1);
    push(tmp2);
}

void clear_s()
{
    stack_p = 0;
}
