#include <stdlib.h>
#include "word_list.h"

struct word_node_tag {
    char *str;
    struct word_node_tag *next;
}; /* typedef in header */

static word_node *word_node_new(const char *str);

word_que *word_que_init(void)
{
    word_que *new = malloc(sizeof(*new));
    if (!new)
        return NULL;

    new->f = new->l = NULL;
    return new;
}

/* return -1 if error */
int word_que_push(word_que *q, const char *str)
{
    word_node *new = word_node_new(str);
    if (!new)
        return -1;

    if (q->f) {
        q->l->next = new;
        q->l = q->l->next;
    } else {
        q->f = q->l = new;
    }

    return 0;
}

char *word_que_pop(word_que *q)
{
    word_node *cur = q->f;
    if (!cur)
        return NULL;

    char *targ = cur->str;
    q->f = q->f->next;
    free(cur);
    return targ;
}

unsigned int word_que_count(word_que *q)
{
    int i;
    word_node *cur;
    for (i = 0, cur = q->f; cur; cur = cur->next)
        i++;
    return i;
}

char **word_que_create_ptr_arr(word_que *q)
{
    unsigned int count = word_que_count(q);
    char **argv = malloc((count+1) * sizeof(char *)); /* +NULL */
    word_node *cur;
    char **runner;
    if (!argv)
        return NULL;

    for(runner = argv, cur = q->f; count > 0; count--, runner++, cur = cur->next)
        *runner = cur->str;
    *runner = NULL;
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
    q->l = NULL;
}

void word_que_dispose(word_que *q)
{
    word_que_clean_words(q);
    free(q);
}

static word_node *word_node_new(const char *str)
{
    word_node *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    new->str  = (char *)str;
    new->next = NULL;
    return new;
}
