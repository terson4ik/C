#include <stdio.h>
#include <stdlib.h>
#include "shell_engine.h"
#include "parser.h"

static void fail_handler(enum fails fail, int c);

int main(void)
{
    parser *p = parser_new();
    if (!p) {
        perror("sh");
        return 1;
    }

    while (!parser_is_eof(p)) {
        enum fails fail;
        fputs("> ", stdout);
        while (!parser_is_eol(p) && !parser_is_eof(p)) {
            if (parser_get_token(p) == -1) {
                perror("sh");
                return 1;
            }
        }
        fail = parser_is_fail(p);
        if (fail != OK) {
            fail_handler(fail, parser_get_error_token(p));
        } else 
        if (parser_get_count_words(p) > 0) {
            char **args = parser_get_argv(p);
            if (!args) {
                perror("sh");
                return 1;
            }
            shell_run_command(args, parser_in_bg(p));
            free(args);
        }

        parser_reset(p);
        shell_clear_zombies();
        fputc('\n', stdout);
    }

    parser_dispose(p);
    return 0;
}

static void fail_handler(enum fails fail, int c)
{
    switch (fail) {
    case QUOTES_ERROR:
        fprintf(stderr, "Error: unmatched quotes\n");
        return;
    case UNEXPECTED_TOKEN_ERROR:
        fprintf(stderr, "Error: syntax error near unexpected tocken '%c'", c);
        return;
    default:
        return;
    }
}
