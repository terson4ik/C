#include <stdio.h>
#include <stdlib.h> /* for exit */
/* example
 * MY FIRST thoughts 
 * I NEED TO THINK ABOUT \ AND LITERALS
 * and additionally 7 var for line, for example
 * line %d: error find } without open bracket 
 * by defoult 1 = 2 = .. = 7 = 0, if variables have negative value then
 * it's error
 * if meet open bracket then increment corresponding var
 * --------closet------------decrement -----------------
 * write func to print message to stderr
 * print_err(int line, char bracket)
 * for comments use define char to diff this case
 * main:
 * c == \n then only ++nl
 * go to handler
 *
 * ENDloop
 */
enum stat_comms {
    START_COM,
    END_COM,
    IN_COM,
    OUT_COM,
    CPP_COM,
    ERR_START,
    FATAL_ERROR
};

enum stat_quotes {
    OUT_Q,
    SINGLE,
    DOUBLE,
    MULT_QUOT,  /* like this "" */
    FATAL_ERR,
};

/* return 0 if ok or ASCII set of char if error */
int hand_brack(int stack[], int *top, int c);
enum stat_comms hand_comm(enum stat_comms state, int c);
enum stat_quotes hand_quot(enum stat_quotes state, int c);

#define STACK_SIZE  1024 /* in good tone will use malloc, but is study */
int main(void)
{
    int nl, c, top, abort;
    enum stat_comms state_com;
    enum stat_quotes state_quot;
    int stack[STACK_SIZE];

/* if enter to comment then skip handling, if EOF and don't exit - error */
    state_com = OUT_COM;
    state_quot = OUT_Q;
    abort = 0;
    nl = 0;
    top = 0;
    while((c = getchar()) != EOF) {
        if(c == '\n')
            ++nl;
        if(c == '\\' && state_com == OUT_COM) {
            getchar();
            continue;
        }
        if(state_com != IN_COM) {
            state_quot = hand_quot(state_quot, c);
            if(state_quot != OUT_Q) {
                if(state_quot == FATAL_ERR) {
                    state_com = OUT_COM;
                    ++nl;
                    break;
                }
                continue;
            }
        }
        state_com = hand_comm(state_com, c);
        if(state_com == FATAL_ERROR) {
            state_quot = OUT_COM;
            ++nl;
            break;
        } else if(state_com == OUT_COM && (c == '{' || c == '}' || c == '[' ||
       /*--if*/c == ']' || c == '(' || c == ')')) {
            abort = hand_brack(stack, &top, c);
            if(abort) {
                ++nl;
                break;
            }
        }
    }
    if(state_com != OUT_COM) {
        fprintf(stderr, "%d: comment don't closet\n", nl);
        return 1;
    }
    if(state_quot != OUT_Q) {
        fprintf(stderr, "%d: quotes don't closet\n", nl);
        return 2;
    }
    if(abort) {
        fprintf(stderr, "%d: %c incorrect\n", nl, c);
        return 3;
    }
    return 0;
}

void print_fatal_stat()
{
    fprintf(stderr, "FATAL ERROR: DOES NOT EXIST THIS STATE\n");
    exit(2);
}

int hand_brack(int stack[], int *top, int c)
{
    switch(c) {
        case '(':
            stack[*top] = '(';
            ++(*top);
            break;
        case ')':
            --(*top);
            if(*top < 0 || stack[*top] != '(')
                return c;
            break;
        case '{':
            stack[*top] = '{';
            ++(*top);
            break;
        case '}':
            --(*top);
            if(*top < 0 || stack[*top] != '{')
                return c;
            break;
        case '[':
            stack[*top] = '[';
            ++(*top);
            break;
        case ']':
            --(*top);
            if(*top < 0 || stack[*top] != '[')
                return c;
            break;
        default:
            print_fatal_stat();
    }
    if(*top > STACK_SIZE - 1) { /* because top index and starts with 0 */
        fprintf(stderr, "HOLY SHIT!!!!!\nSTACK OVERFLOW!!!\n");
        exit(228);
    }
    return 0;
}

enum stat_quotes hand_quot(enum stat_quotes state, int c)
{
    enum stat_quotes t_q = state;
    switch(state) {
        case OUT_Q:
            if(c == '\'')
                t_q = DOUBLE;
            else if(c == '\"')
                t_q = MULT_QUOT;
            break;
        case SINGLE:
            if(c == '\'')
                t_q = OUT_Q;
            else
                t_q = FATAL_ERR;
            break;
        case DOUBLE:
            if(c == '\'')
                t_q = OUT_Q;
            else
                t_q = SINGLE;
            break;
        case MULT_QUOT:
            if(c == '\"')
                t_q = OUT_Q;
            break;
        case FATAL_ERR:
            break;
        default:
            print_fatal_stat();
    }
    return t_q;
}

enum stat_comms hand_comm(enum stat_comms state, int c)
{
    enum stat_comms t_s = state;
    switch(state) {
        case OUT_COM:
            if(c == '/')
                t_s = START_COM;
            break;
        case START_COM:
            if(c == '*')
                t_s = IN_COM;
            else if(c == '/')
                t_s = CPP_COM;
            else
                t_s = OUT_COM;
            break;
        case CPP_COM:
            if(c == '\n')
                t_s = OUT_COM;
            break;
        case IN_COM:
            if(c == '*')
                t_s = END_COM;
            if(c == '/')
                t_s = ERR_START;
            break;
        case ERR_START:
            if(c == '*')
                t_s = FATAL_ERROR;
            break;
        case END_COM:
            if(c == '/')
                t_s = OUT_COM;
            else
                t_s = IN_COM;
            break;
        case FATAL_ERROR:
            /* fatal error */
            break;
        default:
            print_fatal_stat();
    }
    return t_s;
}
