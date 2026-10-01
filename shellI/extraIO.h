#ifndef EXTRA_IO_H_SENTRY
#define EXTRA_IO_H_SENTRY

typedef struct word_tag word;
enum word_status { OK, EOL, QUOT_FAIL, FATAL_ERR };

#define BUF_INIT_SIZE 256
word *word_init(void);
enum word_status get_word(word *w);
char *word_get_buf(word *w);
void word_dispose_struct(word **w);

#endif
