#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "parser.h"
#include "word_list.h"
#include "my_string.h"
#define INIT_BUF_SIZE   255

#define IS_SPACE(c)         ((c) == ' ' || (c) == '\t')
#define SKIP_SPACES(c, inp) for((c) = getc(inp); IS_SPACE(c); (c) = getc(inp));


/* typedef in header */
struct parser_tag {
    vector *cur_word;
    word_que *w_que;

    char *other_std_fd; /* use in handling '>', '<' etc */

    /* errors */
    int          unexpect_err; /* save error char value */
    unsigned int bg_word_err   : 1;
    unsigned int fd_chr_err    : 1;
    unsigned int quot_err      : 1;

    /* output state */
    unsigned int is_eof        : 1;
    unsigned int is_eol        : 1;
    unsigned int is_empy_word  : 1;

    /* private fields */
    unsigned int in_quot       : 1;

    /* handling '&' */
    unsigned int is_and        : 1;
    unsigned int is_bg_work    : 1;

    /* handling '>' ">>" '<' */
    unsigned int fd_append     : 1;
    unsigned int fd_trunc      : 1;
    unsigned int fd_read       : 1;
    unsigned int fd_swap       : 1;
}; 

/* EOF not reset */
static void reset_all(parser *p);
static void reset_line(parser *p);

enum result_of_hand_chr { EXIT, MORE, ERROR };
#define PUSH_AND_RETURN_MORE(v, c) do { \
    vector_push_c(vec, c); \
    return MORE; \
} while(0)

static enum result_of_hand_chr handling_char(parser *p, int c);

static enum result_of_hand_chr handl_in(parser *p);
static enum result_of_hand_chr handl_out(parser *p);
static enum result_of_hand_chr handl_and(parser *p);
static enum result_of_hand_chr handl_quot(parser *p);
static enum result_of_hand_chr handl_skip_c(parser *p);
static enum result_of_hand_chr handl_end_of_situation(parser *p, int is_EOF);
static enum result_of_hand_chr handl_regular_c(parser *p);
static enum result_of_hand_chr handl_semicolon(parser *p);
static enum result_of_hand_chr handl_brackets(parser *p, char bracket);

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

    new->is_eol = 0;
    reset_all(new);
    return new;
}

int parser_get_token(parser *p)
{
    char *str;
    int c;

    SKIP_SPACES(c, stdin);
    while (handling_char(p, c) == MORE)
        c = getchar();

    if (parser_is_fail(p)) {
        reset_line(p);
        return 0;
    }

    if (!vector_buf_is_empty(p->cur_word) || p->is_empy_word) {
        str = mstrdup(vector_get_str(p->cur_word));
        if (!str)
            return -1;
        else if (p->fd_swap)
            p->other_std_fd = str;
        else if (word_que_push(p->w_que, str) == -1)
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

int parser_in_bg(parser *p)
{
    return p->is_bg_work;
}

int parser_get_error_token(parser *p)
{
    return p->unexpect_err;
}

enum fails parser_is_fail(parser *p)
{
    if (p->quot_err)
        return QUOTES_ERROR;
    else if (p->unexpect_err)
        return UNEXPECTED_TOKEN_ERROR;
    else if (p->bg_word_err)
        return UNEXPECTED_TOKEN_ERROR;
    else
        return OK;
}
enum fds parser_io_mode(parser *p)
{
    if (!p->fd_swap)
        return FDS_NONE;

    if (p->fd_read)
        return FDS_IN;
    if (p->fd_append)
        return FDS_OUT;
    if (p->fd_trunc)
        return FDS_TRUNC;

    return FDS_NONE;
}

char *parser_get_file_name_to_fd(parser *p)
{
    return p->other_std_fd;
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
    reset_all(p);
}

void parser_dispose(parser *p)
{
    vector_dispose(p->cur_word);
    word_que_dispose(p->w_que);
    free(p);
}


static enum result_of_hand_chr handling_char(parser *p, int c)
{
    if (p->in_quot && c != EOF && c != '\n')
        PUSH_AND_RETURN_MORE(p->cur_word, c);

    switch (c) {
    case '>':  return handl_out(p);
    case '<':  return handl_in(p);
    case '&':  return handl_and(p);
    case '|':  return handl_or(p);
    case ';':  return handl_semicolon(p);
    case '(':  return handl_brackets(p, '(');
    case ')':  return handl_brackets(p, ')');
    case '\"': return handl_quot(p);
    case '\\': return handl_skip_c(p);
    case '\t': return EXIT;
    case ' ':  return EXIT;
    case '\n': return handl_end_of_situation(p, 0);
    case EOF:  return handl_end_of_situation(p, EOF);
    default:   return handl_regular_c(p);
    }
}

static void reset_all(parser *p)
{
    p->bg_word_err   = 0;
    p->quot_err      = 0;
    p->unexpect_err  = 0;
    p->fd_chr_err    = 0;

    p->is_eol        = 0;
    p->is_empy_word  = 0;

    p->in_quot       = 0;

    p->is_bg_work    = 0; 
    p->is_and        = 0;

    if (p->other_std_fd) {
        free(p->other_std_fd);
        p->other_std_fd = NULL;
    }
    p->fd_append     = 0;
    p->fd_trunc      = 0;
    p->fd_read       = 0;
    p->fd_swap       = 0;
}

static void reset_line(parser *p)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {}

    if (c == '\n')
        p->is_eol = 1;
    else if (c == EOF)
        p->is_eof = 1;
}

static enum result_of_hand_chr handl_in(parser *p);
{
    if (p->fd_swap || p->fd_read ) {
        p->fd_chr_err = 1;
        return ERROR;
    } else {
        p->fd_read = 1;
        p->fd_swap = 1;
        return MORE;
    }
}

static enum result_of_hand_chr handl_out(parser *p);
{
    if (p->fd_read)
        return ERROR;

    if (!p->fd_trunc) {
        p->fd_trunc = 1;
    } else if (!p->fd_append) {
        p->fd_append = 1;
    } else {
        p->unexpect_err = '>';
        return ERROR;
    }

    p->fd_swap = 1;
    return MORE;
}

static enum result_of_hand_chr handl_and(parser *p);
{
    if (p->is_bg_work) {
        p->is_bg_work = 0;
        p->is_and = 1;
    } else if (p->is_and) {
        p->unexpect_err = '&';
        return ERROR;
    } else {
        p->is_bg_work = 1;
    }
    return MORE;
}

static enum result_of_hand_chr handl_quot(parser *p)
{
    p->in_quot = !p->in_quot;
    p->is_empy_word = 1;
    return MORE;
}

static enum result_of_hand_chr handl_skip_c(parser *p)
{
    int c = getchar();
    if (c != EOF)
        PUSH_AND_RETURN_MORE(p->cur_word, c);
    else {
        p->is_eof = 1;
        return ERROR;
    }
}

static enum result_of_hand_chr handl_end_of_situation(parser *p, int is_EOF)
{
    if (p->in_quot) {
        p->quot_err = 1;
        return ERROR;
    }

    if (is_eof)
        p->is_eof = 1;
    else
        p->is_eol = 1;

    return EXIT;
}

static enum result_of_hand_chr handl_regular_c(parser *p)
{
    if (p->is_bg_work) {
        p->bg_word_err  = 1;
        p->unexpect_err = '&';
        return ERROR;
    } else if (p->fd_swap && !p->other_std_fd) {
        p->fd_chr_err = 1;
        return ERROR;
    }

    PUSH_AND_RETURN_MORE(p->cur_word, c);
}

static enum result_of_hand_chr handl_semicolon(parser *p)
{
    fputs("Feature not implemented yet\n", stderr);
    return EXIT;
}

static enum result_of_hand_chr handl_brackets(parser *p, char bracket)
{
    fputs("Feature not implemented yet\n", stderr);
    return EXIT;
}
