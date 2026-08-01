/* ex 5.10: _2*(3+4)_ = _expr 2 3 4 + *_ */
#include <stdio.h>
#include <stdlib.h>

/* TODO: hide implementation of stack */
int pop(); /* or pop(int stack[], int pointer, int st_size) */
void push(int x); /* or push(int x, int stack[], int pointer, int st_size) */
int is_empty(); /* or is_(int stack[], int pointer) */
int strtoi(const char *s); /* atoi from stdlib */
#define IS_NUM(x) (((x) >= '0' && (x) <= '9') ? 1 : 0) /* isnumber from ctype.h */

/* get numbers to stack; if meet operation, then pop numbers */
int main(int argc, char **argv) 
{
    char **save_argv = argv;
    while (*++save_argv != NULL) {
        int c = **save_argv;
        int op2;
        if ((c == '+' || c == '-') && IS_NUM(*(*save_argv + 1))) {
                push (strtoi(*save_argv));
                continue;
            }
        if (!IS_NUM(c) && *(*save_argv + 1) != '\0') {
                fprintf(stderr, "Invalid input: %s", *save_argv);
                return 1;
            }
        switch (c) {
        /* case is_number processed in default branch */
            case '+':
                push(pop() + pop()); /* associative law */
                break;
            case '*':
                push(pop() * pop()); /* associative law */
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (!op2) {
                    fputs("divided to zero DENIED\n", stderr);
                    return 2;
                }
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                if (!op2) {
                    fputs("divided to zero DENIED\n", stderr);
                    return 2;
                }
                push(pop() % op2);
                break;
            default:
                if (IS_NUM(c))
                    push (strtoi(*save_argv));
                else {
                    fprintf(stderr, "Unknown operator: %c\n", c);
                    return 1;
                }
                break;
        }
    }
    printf("Result: %d\n", pop());
    if (!is_empty()) {
        fputs("STACK IS NOT EMPTY\n", stderr);
        return 4;
    } else
        return 0;
}

int strtoi(const char *s)
{
    int res, sign = 1;
    
    if (!IS_NUM(*s) && (*s == '-'  || *s == '+')) {
        sign = (*s == '-') ? -1 : 1;
        s++;
    } else if (!IS_NUM(*s)) {
        fprintf(stderr, "ABORT: detected a non number: %s\n", s);
        exit(9);
    }
    for (res = 0; IS_NUM(*s); s++)
        res = res * 10 + *s - '0';
    return res * sign;
}

#define INT_STACK_SIZE 100
static int int_stack[INT_STACK_SIZE];
static int *pstack = int_stack;

#define ERR_VAL -1
#define ERR_MSG_EMPTY_STACK "Stack is empty....ABORT!\n"
#define ERR_MSG_OVERFLOW_STACK "Stack is overflow. ABORT!\n"
int pop()
{
    if (pstack <= int_stack) {
        fputs(ERR_MSG_EMPTY_STACK, stderr);
        exit(3);
    }
    return *--pstack;
}
void push(int x)
{
    if (pstack >= int_stack + INT_STACK_SIZE) {
        fputs(ERR_MSG_OVERFLOW_STACK, stderr);
        exit(3);
    } else
        *pstack++ = x;
}

int is_empty()
{
    return pstack == int_stack;
}
