#include <stdio.h>
#include <stdlib.h>
#include "shell_engine.h"
#include "parser.h"

int main(void)
{
    parser *p = parser_new();
    if (!p) {
        perror("sh");
        return 1;
    }

    while (!parser_is_eof(p)) {
        fputs("> ", stdout);
        while (!parser_is_eol(p) && !parser_is_eof(p)) {
            if (parser_get_token(p) == -1) {
                perror("sh");
                return 1;
            }
        }
        if (parser_get_count_words(p) > 0) {
            char **args = parser_get_argv(p);
            if (!args) {
                perror("sh");
                return 1;
            }
            run_command(args);
            free(args);
        }

        parser_reset(p);
        fputc('\n', stdout);
    }

    parser_dispose(p);
    return 0;
}
