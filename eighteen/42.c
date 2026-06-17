#include <stdio.h>
#include <stdlib.h>

struct node_char {
    char c;
    struct node_char *next;
};

struct que { /* for fast access to last node of char */
    struct node_char *first, *last;
};
typedef struct que queue;

struct node_word {
    queue *q;
    struct node_word *next;
};
typedef struct node_word stack_words;

/* public API */
void s_push(stack_words **p_stack, char c);
void s_print_all(stack_words **p_stack);
int main(void)
{
    int c;
    stack_words *stack_w = NULL;
    while((c = getchar()) != EOF) {
        if(c != '\n')
            s_push(&stack_w, c);
        else
            s_print_all(&stack_w);
    } /* if EOF without '\n' need to check */
    s_print_all(&stack_w);
    return 0;
}

void s_pop(stack_words **p_stack, char *c);
void s_print_all(stack_words **p_stack)
{
    char tmp_c;
    if(!(*p_stack))
        return;
    s_pop(&(*p_stack), &tmp_c);
    if(tmp_c != ' ') /* if last char before '\n' space, then rm it */
        putchar(tmp_c);
    while(*p_stack) {
        s_pop(&(*p_stack), &tmp_c);
        putchar(tmp_c);
    }
    putchar('\n');
}

void s_init(stack_words **p_stack)
{
    *p_stack = malloc(sizeof(stack_words));
    (*p_stack)->next = NULL;
    /* straightaway fill queue of chars */
    (*p_stack)->q = malloc(sizeof(queue));
    (*p_stack)->q->first = NULL;
    (*p_stack)->q->last = NULL;
}

void q_push_c(queue **q, char c);
void s_push(stack_words **p_stack, char c)
{
    if(*p_stack == NULL)
        s_init(&(*p_stack));
    if(c != ' ' && c != '\t') {
        /* for each push `c` p_stack will allocated */
        q_push_c(&(*p_stack)->q, c);
        return;
    }
    if((*p_stack)->q->first != NULL) {
        /* meet space then create new node */
        stack_words *tmp;
        s_init(&tmp);
        tmp->next = *p_stack;
        (*p_stack) = tmp;
    }
}

void q_push_c(queue **q, char c)
{
    struct node_char *tmp = malloc(sizeof(*tmp));
    tmp->c = c;
    tmp->next = NULL;
    if((*q)->first != NULL) {
        (*q)->last->next = tmp;
        (*q)->last = tmp;
    } else /* init the very first node */
        (*q)->first = (*q)->last = tmp;
}

void s_pop(stack_words **p_stack, char *c)
{
    struct node_char *tmp = (*p_stack)->q->first;
    if(tmp != NULL) {
        *c = tmp->c;
        (*p_stack)->q->first = (*p_stack)->q->first->next;
        free(tmp);
    } else { /* word end -> give space and remove empty node */
        stack_words *cur = *p_stack;
        *c = ' ';
        *p_stack = (*p_stack)->next;
        free(cur->q);
        free(cur);
    }
}
