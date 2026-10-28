#include "vector"
#include "word_list.h"

/* typedef in header */
struct parser_tag {
    vector cur_word;
    word_que w_que;
    int last_c;
    unsigned int w_count;
    unsigned int is_eol  : 1;
    unsigned int is_eof  : 1;
    unsigned int in_quot : 1;
}; 

parser parser_new(void)
{
    return 0;
}

int parser_get_token(parser *p)
{
    return 0;
}

int parser_is_eof(parser *p)
{
    return 0;
}

int parser_is_eol(parser *p)
{
    return 0;
}

char **parser_get_argv(parser *p)
{
    return 0;
}

char *parser_get_first_w(parser *p)
{
    return 0;
}

char *parser_get_last_w(parser *p)
{
    return 0;
}

void parser_reset(parser *p)
{
}

void parser_dispose(parser *p)
{
}
