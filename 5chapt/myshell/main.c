#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "shell_engine.h"
#include "parser.h"

static void fail_handler(enum fails fail, int c);
static int convert_fds_to_mode(enum fds fds_var);
static int convert_fds_to_fd(enum fds fds_var);

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
            char remap_std_fd = parser_io_mode(p) != FDS_NONE;
            int save1fd, fd;

            if (!args) {
                perror("sh");
                return 1;
            }
            if (remap_std_fd) {
                fd = open(parser_get_file_name_to_fd(p),
                          convert_fds_to_mode(p), 0666);
                if (fd == -1) {
                    perror(parser_get_file_name_to_fd(p));
                    free(args);
                    goto clean_sh
                }
                save1fd = dup(convert_fds_to_fd(p));
                dup2(fd, convert_fds_to_fd(p));
                close(fd);
            }
            shell_run_command(args, parser_in_bg(p));
            free(args);
            if (remap_std_fd)
                dup2(save1fd, convert_fds_to_fd(p));
        }
clean_sh:
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

static int convert_fds_to_mode(enum fds fds_var)
{
    switch (fds_var) {
    case FDS_IN:    return O_RDONLY;
    case FDS_OUT:   return O_APPEND | O_WRONLY | O_CREAT;
    case FDS_TRUNC: return O_TRUNC  | O_WRONLY | O_CREAT;
    case FDS_NONE:  return 0;
    default:        return 0;
    }
}

static int convert_fds_to_fd(enum fds fds_var)
{
    switch (fds_var) {
    case FDS_IN:    return 0;
    case FDS_OUT:   return 1;
    case FDS_TRUNC: return 1;

    case FDS_NONE:  return -1;
    default:        return -1;
    }
}
