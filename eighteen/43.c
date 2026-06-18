#include <stdio.h>
#include <stdlib.h>

struct node_char {
    char c;
    struct node_char *next;
};
struct q_char {
    struct node_char *first, *last;
};
typedef struct q_char queue_char;

struct node_word {
    queue_char *q_c;
    unsigned long long length;
    struct node_word *next;
};
struct q_word {
    struct node_word *first, *last;
};
typedef struct q_word queue_word;

/* push also automatically init empty list + auto divides new words */
void q_word_push(queue_word **ptr_q_w, char c);
/* printing also free memory after pop */
void q_word_print_all(queue_word **ptr_q_w);
int main(void)
{
    queue_word *q_w = NULL;
    int c;
    while((c = getchar()) != EOF)
        if(c != '\n')
            q_word_push(&q_w, c);
        else
            q_word_print_all(&q_w);
    /* in case when '\n' not entered */
    q_word_print_all(&q_w);
    return 0;
}

void q_word_init(queue_word **ptr_q_w);
void w_node_init(struct node_word **ptr_w);
void q_char_push(queue_char **ptr_q_c, char c);
/* push also automatically init empty list + auto divides new words */
void q_word_push(queue_word **ptr_q_w, char c)
{
    if(!*ptr_q_w)
        q_word_init(ptr_q_w);
    if(c != ' ' && c != '\t') {
        q_char_push(&(*ptr_q_w)->last->q_c, c);
        ++(*ptr_q_w)->last->length;
        return;
    } /* if c space then */
    if((*ptr_q_w)->last->q_c->first != NULL) {
        struct node_word *tmp_w;
        w_node_init(&tmp_w);
        (*ptr_q_w)->last->next = tmp_w;
        (*ptr_q_w)->last = (*ptr_q_w)->last->next;
    }
}

void w_node_init(struct node_word **ptr_w)
{
    (*ptr_w) = malloc(sizeof(struct node_word));
    (*ptr_w)->q_c = malloc(sizeof(queue_char));
    (*ptr_w)->q_c->last = (*ptr_w)->q_c->first = NULL;
    (*ptr_w)->length = 0;
    (*ptr_w)->next = NULL;
}
void q_word_init(queue_word **ptr_q_w)
{
    *ptr_q_w = malloc(sizeof(queue_word));
    w_node_init(&(*ptr_q_w)->first);
    (*ptr_q_w)->last = (*ptr_q_w)->first;
}
void q_char_push(queue_char **ptr_q_c, char c)
{
    struct node_char *tmp_node_c= malloc(sizeof(*tmp_node_c));
    tmp_node_c->c = c;
    tmp_node_c->next = NULL;
    if((*ptr_q_c)->first != NULL) {
        (*ptr_q_c)->last->next = tmp_node_c;
        (*ptr_q_c)->last = (*ptr_q_c)->last->next;
    } else
        (*ptr_q_c)->last = (*ptr_q_c)->first = tmp_node_c;
}
/* printing also free memory after pop */
char q_char_pop_c(queue_char **ptr_q_c);
void q_word_print_all(queue_word **ptr_q_w)
{
    unsigned long long max;
    queue_word *orig_node = *ptr_q_w;
    if(!*ptr_q_w || !(*ptr_q_w)->first)
        return;
    do {
    struct node_word *cur = (*ptr_q_w)->first;
        max = 0;
        while(cur) {
            if(cur->length != 0) {
                --cur->length;
                if(max < cur->length)
                    max = cur->length;
                putchar(q_char_pop_c(&cur->q_c));
            } else
                putchar(' ');
            cur = cur->next;
        }
        putchar('\n');
    } while(max);
    /* if max = 0 then all nodes with chars is empty; remove words nodes */
    while((*ptr_q_w)->first) {
        struct node_word *cur = (*ptr_q_w)->first;
        free((*ptr_q_w)->first->q_c);
        (*ptr_q_w)->first = (*ptr_q_w)->first->next;
        free(cur);
    }
    free(orig_node);
    *ptr_q_w = NULL;
}
char q_char_pop_c(queue_char **ptr_q_c)
{
    char c;
    struct node_char *cur = (*ptr_q_c)->first;
    c = cur->c;
    (*ptr_q_c)->first = (*ptr_q_c)->first->next;
    free(cur);
    return c;
}
