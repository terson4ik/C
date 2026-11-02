#ifndef PARSER_H_SENTRY
#define PARSER_H_SENTRY

typedef struct parser_tag parser;

enum fails { OK, QUOTES_ERROR, UNEXPECTED_TOKEN_ERROR };
enum fds { FDS_NONE, FDS_IN, FDS_OUT, FDS_TRUNC };

parser *parser_new(void);
int parser_get_token(parser *p);
unsigned int parser_get_count_words(parser *p);
int parser_is_eof(parser *p);
int parser_is_eol(parser *p);
int parser_in_bg(parser *p);
int parser_get_error_token(parser *p);
enum fails parser_is_fail(parser *p);
enum fds parser_io_mode(parser *p);
char *parser_get_file_name_to_fd(parser *p);

char **parser_get_argv(parser *p);
char *parser_get_first_w(parser *p);
void parser_reset(parser *p);

void parser_dispose(parser *p);

#endif
