#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OP  100
#define NUMBER  '0'

void push(double x);
double pop(void);
int get_op(char s[]);

int main()
{
    char s[MAX_OP];
    double op2;
    int type;

    while((type = get_op(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
                printf("\t%.8g\n", pop());
                break;
            default:
                fprintf(stderr, "Incorrect operator/operand: %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAX_VAL 100

double val[MAX_VAL];
int stack_p = 0;

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
        fprintf(stderr, "Impossible to give a non stack range(< 0)\n");
        return 0.0;
    }
}

int getch();
void ungetch(int c);

int get_op(char s[])
{
    int c, i; /* need `c` to catch EOF */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '+' && c != '-')
        return c;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return s[0];
        }
        s[1] = c;
    }
    i = (s[1] == '\0') ? 0 : 1;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define INP_MAX 100

int chars[INP_MAX];
int chr_ptr = 0;

int getch()
{
    return (chr_ptr > 0) ? chars[--chr_ptr] : getchar();
}
    
void ungetch(int c)
{
    if (chr_ptr >= INP_MAX)
        fprintf(stderr, "TOO MANY CHARACTERS\n");
    else
        chars[chr_ptr++] = c;
}
