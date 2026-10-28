#ifndef PARSER_H_SENTRY
#define PARSER_H_SENTRY

typedef struct parser_tag parser;

parser parser_new(void);
int parser_get_token(parser *p);
int parser_is_eof(parser *p);
int parser_is_eol(parser *p);

char **parser_get_argv(parser *p);
char *parser_get_first_w(parser *p);
char *parser_get_last_w(parser *p);
void parser_reset(parser *p);

void parser_dispose(parser *p);

#endif
