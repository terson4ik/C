#ifndef WORD_LIST_H_SENTRY
#define WORD_LIST_H_SENTRY

typedef struct word_item_tag word_item;

typedef struct {
    word_item *f, *l;
} word_que;

void word_que_init(word_que *q);
int word_que_add(word_que *q, char *buf);                     
void word_item_execute(const word_item *f);
void word_item_dispose(word_item **f);

#endif
