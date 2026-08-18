/* 7.5 */
#include <stdio.h>
#include <ctype.h>

#define MAXSTACK 500
static void push(double x);
static double pop();
static int is_empty();

#define MAXLINE 256
int get_word(char *w, int lim);

int main()
{
    char line[MAXLINE];
    double operand;

    while (get_word(line, MAXLINE) > 0)
        if (sscanf(line, "%lf", &operand) == 1)
            push(operand);
        else 
            switch (*line) {
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    operand = pop();
                    push(pop() - operand);
                    break;
                case '/':
                    operand = pop();
                    push(pop() / operand);
                    break;
                case '%':
                    operand = pop();
                    push((double)((int)pop() % (int)operand));
                    break;
                case '\n':
                    if (is_empty()) {
                        fprintf(stderr, "stack empty\n");
                        return 1;
                    } else
                        printf("%f\n", pop());
                    break;
                default:
                    fprintf(stderr, "unknown value: %s\n", line);
                    return 1;
                    break;
            }
    return 0;
}

int get_word(char *w, int lim)
{
    char *save = w;
    int c;
    if (lim <= 1)
        return 0;

    while (isspace(c = getchar()) && c != '\n')
        ;
    if (c == EOF)
        return EOF;
    *w++ = c;
    if (c == '\n')
        goto exit;
    while (--lim > 0 && (c = getchar()) != EOF && !isspace(c))
        *w++ = c;
    ungetc(c, stdin);
exit:
    *w = '\0';
    return w - save;
}

static double stack[MAXSTACK];
static double *sp = stack;

static void push(double x)
{
    if (sp >= stack + MAXSTACK)
        fprintf(stderr, "stack oveflow... ignore: %f\n", x);
    else
        *sp++ = x;
}
static double pop()
{
    if (is_empty()) {
        fprintf(stderr, "stack empty... return 0.0");
        return 0.0;
    } else
        return *--sp;
}

static int is_empty()
{
    return sp == stack;
}
