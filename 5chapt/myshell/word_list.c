#include <stdlib.h>
#include "word_list.h"

static word_node_new(const char *str);

word_que word_que_init()
{
    word_que *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    word_que_ptr_fill_nulls(new);
    return new;
}

/* alternative quick init*/
void word_que_ptr_fill_nulls(word_que *q)
{
    q->f = q->l = NULL;
}

/* return -1 if error */
int word_que_push(word_que *q, const char *str)
{
    word_node *new = word_node_new(str);
    if (!new)
        return -1;

    if (q->f) {
        q->l->next = new;
        q->l = q->l->next
    } else {
        q->f = q->l = new;
    }

    return 0;
}

char *word_que_pop(word_que *q)
{
    word_node *cur = q->f;
    char *targ = cur->str;
    q->f = q->f->next;
    free(cur);
    return targ;
}

unsigned int word_que_count(word_node *wn)
{
    int i;
    for (i = 0; wn; wn = wn->next, i++)
    {}
    return i;
}

char **word_que_create_ptr_arr(word_que *q)
{
    unsigned i = word_que_count(q->f);
    char **argv = malloc(i * sizeof(char *));
    char **runner;
    if (!argv)
        return NULL;

    for(runner = argv; i > 0; i--, runner++, q->f = q->f->next)
        *runner = q->f->str;

    return argv;
}

void word_que_clean_words(word_que *q)
{
    while (q->f) {
        word_node *cur = q->f;
        q->f = q->f->next;
        free(cur->str);
        free(cur);
    }
}

void word_que_dispose(word_que *q)
{
    word_que_clean_words(q);
    free(q);
}

static word_node *word_node_new(const char *str)
{
    word_node *new = malloc(sizeof(*new));
    new->str  = str;
    new->next = NULL;
    return new;
}
