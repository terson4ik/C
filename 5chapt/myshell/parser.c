#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "parser.h"
#include "word_list.h"
#include "my_string.h"

/* typedef in header */
struct parser_tag {
    vector *cur_word;
    word_que *w_que;
    unsigned int is_eol        : 1;
    unsigned int is_empy_word  : 1;
    unsigned int is_eof        : 1;
    unsigned int is_syntax_err : 1;
    unsigned int in_quot       : 1;
    unsigned int need_skip     : 1;
}; 

#define INIT_BUF_SIZE   4096

#define IS_SPACE(c)         ((c) == ' ' || (c) == '\t')
#define SKIP_SPACES(c, inp) for((c) = getc(inp); IS_SPACE(c); (c) = getc(inp));

enum result_of_hand_chr { EXIT, MORE, ERROR };
static enum result_of_hand_chr handling_char(parser *p, int c);

parser *parser_new(void)
{
    parser *new = malloc(sizeof(*new));
    if (!new)
        return NULL;

    new->cur_word = vector_init(INIT_BUF_SIZE);
    if (!new->cur_word) {
        free(new);
        return NULL;
    }

    new->w_que = word_que_init();
    if (!new->w_que) {
        vector_dispose(new->cur_word);
        free(new);
        return NULL;
    }

    new->is_eol        = 0;
    new->is_eof        = 0;
    new->in_quot       = 0;
    new->need_skip     = 0;
    new->is_empy_word  = 0;
    new->is_syntax_err = 0;
    return new;
}

int parser_get_token(parser *p)
{
    char *str;
    int c;

    SKIP_SPACES(c, stdin);
    while (handling_char(p, c) == MORE)
        c = getchar();

    if (parser_is_fail(p))
        return 0;

    if (!vector_buf_is_empty(p->cur_word) || p->is_empy_word) {
        str = mstrdup(vector_get_str(p->cur_word));
        if (!str)
            return -1;
        if (word_que_push(p->w_que, str) == -1)
            return -1;

        vector_buf_reset(p->cur_word);
        p->is_empy_word = 0;
    }
    return 0;
}

unsigned int parser_get_count_words(parser *p)
{
    return word_que_count(p->w_que);
}

int parser_is_eof(parser *p)
{
    return p->is_eof;
}

int parser_is_eol(parser *p)
{
    return p->is_eol;
}

enum fails parser_is_fail(parser *p)
{
    if (p->is_syntax_err)
        return QUOTES_ERROR;
    else
        return OK;
}

char **parser_get_argv(parser *p)
{
    return word_que_create_ptr_arr(p->w_que);
}

char *parser_get_first_w(parser *p)
{
    return word_que_pop(p->w_que);
}

void parser_reset(parser *p)
{
    vector_buf_reset(p->cur_word);
    word_que_clean_words(p->w_que);
    p->in_quot       = 0;
    p->is_eol        = 0;
    p->is_syntax_err = 0;
    p->is_empy_word  = 0;
    p->need_skip     = 0;
}

void parser_dispose(parser *p)
{
    vector_dispose(p->cur_word);
    word_que_dispose(p->w_que);
    free(p);
}

static enum result_of_hand_chr handling_char(parser *p, int c)
{
    if (p->need_skip) {
        p->need_skip = 0;
        vector_push_c(p->cur_word, c);
        return MORE;
    }

    switch (c) {
    case '\"':
        p->in_quot = !p->in_quot;
        p->is_empy_word = 1;
        return MORE;
    case '\\':
        p->need_skip = 1;
        return MORE;
    case '\t':
    case ' ':
        if (p->in_quot) {
            vector_push_c(p->cur_word, c);
            return MORE;
        } else {
            return EXIT;
        }
    case '\n':
        p->is_eol = 1;
        if (p->in_quot) {
            p->is_syntax_err = 1;
            return ERROR;
        }
        return EXIT;
    case EOF:
        p->is_eof = 1;
        if (p->in_quot) {
            p->is_syntax_err = 1;
            return ERROR;
        }
        return EXIT;
    default:
        vector_push_c(p->cur_word, c);
        return MORE;
    }
}
