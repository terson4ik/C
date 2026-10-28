#ifndef WORD_LIST_H_SENTRY
#define WORD_LIST_H_SENTRY

typedef struct word_node_tag word_node;

typedef struct {
    word_node *f, *l;
} word_que;


word_que *word_que_init(void);

/* return -1 if error */
int word_que_push(word_que *q, const char *str);
char *word_que_pop(word_que *q);

unsigned int word_que_count(word_que *q);
char **word_que_create_ptr_arr(word_que *q);

void word_que_clean_words(word_que *q);
void word_que_dispose(word_que *q);

#endif
