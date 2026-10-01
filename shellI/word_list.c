#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_list.h"

/* typedef in header file */
struct word_item_tag {
    char *word;
    struct word_item_tag *next;
};

static word_item *new_word_elem(char *buf);

void word_que_init(word_que *q)
{
    q->f = NULL;
}

int word_que_add(word_que *q, char *buf)
{
    word_item *new = new_word_elem(buf);
    if (!new)
        return 0;

    if (q->f) {
        q->l->next = new;
        q->l = q->l->next;
    } else {
        q->f = q->l = new;
    }

    return 1;
}

void word_item_execute(const word_item *f)
{
    for ( ; f; f = f->next)
        printf("[%s]\n", f->word);
}

void word_item_dispose(word_item **f)
{
    while (*f) {
        word_item *cur = *f;
        (*f) = (*f)->next;

        free(cur->word);
        free(cur);
    }
}

static word_item *new_word_elem(char *buf)
{
    word_item *elem = malloc(sizeof(*elem));
    if (!elem)
        return NULL;

    elem->word = strdup(buf);
    if (!elem->word) {
        free(elem);
        return NULL;
    }

    elem->next = NULL;
    return elem;
}
