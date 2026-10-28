#ifndef WORD_LIST_H_SENTRY
#define WORD_LIST_H_SENTRY

typedef struct word_node_tag {
    char *str;
    struct word_node_tag *next;
} word_node;

typedef struct {
    word_node *f, *l;
} word_que;


word_que word_que_init(void);

/* alternative quick init*/
void word_que_ptr_fill_nulls(word_que *q);

/* return -1 if error */
int word_que_push(word_que *q, const char *str);
char *word_que_pop(word_que *q);

unsigned int word_que_count(word_node *wn);
char **word_node_create_ptr_arr(word_node *wn);

void word_que_clean_words(word_que *q);
void word_que_dispose(word_que *q);

#endif
