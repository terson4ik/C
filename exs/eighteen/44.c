#include <stdio.h>
#include <stdlib.h>

struct chr_node {
    char c;
    struct chr_node *next;
};
struct que_chr {
    struct chr_node *first, *last;
};
typedef struct que_chr queue_chars;

struct word_node {
    queue_chars *q_c;
    unsigned long length;
    struct word_node *next;
};
struct que_word {
    struct word_node *first, *last;
};
typedef struct que_word queue_word;

/* auto initial empty queue and push only digit. Letters will ignored */
void q_w_push_dig(queue_word **ptr_q_w, char c);
/* also free memory with popping chars */
void q_w_print_largest(queue_word **ptr_q_w);
int main(void)
{
    queue_word *q_words = NULL;
    int c;
    while((c = getchar()) != EOF)
        if(c != '\n')
            q_w_push_dig(&q_words, c);
        else
            q_w_print_largest(&q_words);
    /* in case if stdin dont contain '\n'| automatic check empty list enable*/
    q_w_print_largest(&q_words);
    return 0;
}

void q_w_init(queue_word **ptr_q_w);
void q_c_push(queue_chars **ptr_q_c, char c);
struct word_node *wrd_nd_new();
void q_w_push_dig(queue_word **ptr_q_w, char c)
{ /* auto initial empty queue and push only digit. Letters will ignored */
    if(!*ptr_q_w)
        q_w_init(ptr_q_w);

    if(c >= '0' && c <= '9') {
        q_c_push(&(*ptr_q_w)->last->q_c, c);
        ++(*ptr_q_w)->last->length;

    } else
        if((*ptr_q_w)->first->q_c->first != NULL) {
            struct word_node *new_word = wrd_nd_new();
            (*ptr_q_w)->last->next = new_word;
            (*ptr_q_w)->last = new_word;
        }
}

void q_w_init(queue_word **ptr_q_w)
{
    struct word_node *new_word = wrd_nd_new();
    (*ptr_q_w) = malloc(sizeof(queue_word));
    if(!*ptr_q_w)
        perror("In function q_w_init, in malloc new queue if words");

    (*ptr_q_w)->last = (*ptr_q_w)->first = new_word;
}
struct word_node *wrd_nd_new()
{
    struct word_node *new_word = malloc(sizeof(struct word_node));
    if(!new_word)
        perror("In function wrd_nd_new, in malloc new word");

    new_word->q_c = malloc(sizeof(queue_chars));
    if(!new_word->q_c)
        perror("In function wrd_nd_new, in malloc new queue of chars");

    new_word->q_c->last = new_word->q_c->first = NULL;
    new_word->length = 0;
    new_word->next = NULL;
    return new_word;
}

void q_c_push(queue_chars **ptr_q_c, char c)
{
    struct chr_node *new_chr_nd = malloc(sizeof(*new_chr_nd));
    if(!new_chr_nd)
        perror("In function q_c_push, in malloc new node of char");

    new_chr_nd->c = c;
    new_chr_nd->next = NULL;

    if((*ptr_q_c)->first != NULL) {
        (*ptr_q_c)->last->next = new_chr_nd;
        (*ptr_q_c)->last = (*ptr_q_c)->last->next;
    } else
        (*ptr_q_c)->last = (*ptr_q_c)->first =new_chr_nd;
}

void chr_n_print_node(struct chr_node *chr_n);
void q_w_free(queue_word **ptr_q_w);
void q_w_print_largest(queue_word **ptr_q_w)
{ /* also free memory with popping chars */
    int max = 0;
    struct word_node *tmp_word_nd;
    if(!*ptr_q_w)
        return;

   tmp_word_nd = (*ptr_q_w)->first;
   while(tmp_word_nd) {
        if(max < tmp_word_nd->length)
            max = tmp_word_nd->length;

        tmp_word_nd = tmp_word_nd->next;
    }
    
    if(max) {
        struct word_node *tmp_w = (*ptr_q_w)->first;
        while(tmp_w) {
            if(tmp_w->length == max) {
                chr_n_print_node(tmp_w->q_c->first);
                putchar(' ');
            }

            tmp_w = tmp_w->next;
        }
    }
    putchar('\n');

    q_w_free(ptr_q_w);
}

void chr_n_print_node(struct chr_node *chr_n)
{
    for(; chr_n; chr_n = chr_n->next)
        putchar(chr_n->c);
}

void q_w_free(queue_word **ptr_q_w)
{
    if(!*ptr_q_w)
        return;

    /* 4 steps: queue words -> node word -> queue chars -> node char */
    while((*ptr_q_w)->first) {
        struct word_node *cur_w = (*ptr_q_w)->first;

        if((*ptr_q_w)->first->q_c != NULL) {
            while((*ptr_q_w)->first->q_c->first) {
                struct chr_node *cur_c = (*ptr_q_w)->first->q_c->first;
                (*ptr_q_w)->first->q_c->first = (*ptr_q_w)->first->q_c->first->next;
                free(cur_c);
            }
            free((*ptr_q_w)->first->q_c);
        }

        (*ptr_q_w)->first = (*ptr_q_w)->first->next;
        free(cur_w);
    }

    free(*ptr_q_w);
    *ptr_q_w = NULL;
}
