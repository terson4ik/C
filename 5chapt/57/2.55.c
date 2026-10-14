#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* own implementation; study reason(!) */
static size_t str_len(const char *s);
static int str_str(const char *s1, const char *s2);
static int str_case_str(const char *s1, const char *s2);
static int str_n_str(const char *s1, const char *s2, ssize_t size);

enum os_halts {
    ARGS_ERROR = 1,
    FILE_ERROR = 2
};
enum node_info {
    STR_MAX_SIZE   = 60, 
    INT_WID        = 4, 
    FIELD_MAX_SIZE = STR_MAX_SIZE + INT_WID
};
enum operations { ADD, QUERY, LIST, UNKNOWN };
enum exit_codes { OK = 0, ERR = -1 };

/* !!! handling() and dirty_* use exit() !!! */
static void handling_args(const char *file_nm, const char *command,
                          const char *field);
static enum operations get_operation(const char *s);
static enum exit_codes add(const char *name, int fd);
/* also return exit_codes(-1) */
static unsigned int query(const char *name, int fd);
static exit_codes list(int fd);
static exit_codes read_one_node(int fd, char buf[FIELD_MAX_SIZE]);

static int dirty_open(const char *name, int mode, int perms);
static void unsopported_file_halt(const char *name);

static const char no_args_msg[]     = "Usage: bd FILE COMMAND <FIELD>\n";
static const char commands_msg[]    = "Supported: add query list\n";
static const char empty_field_msg[] = "No field specified\n";

int main(int argc, char **argv)
{
    if (argc < 3) {
        write(STDERR_FILENO, no_args_msg, sizeof(no_args_msg)-1);
        return ARGS_ERROR;
    }

    if (argv[3] && str_len(argv[3]) >= FIELD_MAX_SIZE) {
        fprintf(stderr, "Too long field. Max length %d", STR_MAX_SIZE);
        return ARGS_ERROR;
    }

    handling_args(argv[1], argv[2], argv[3]);

    return 0;
}


static void handling_args(const char *file_nm, const char *command,
                          const char *field)
{
    enum { WRAP_PERMS = 0 };
    enum exit_codes status;
    int fd;
    enum operations oper = get_operation(command);
    if (oper != LIST && !field) {
        write(STDERR_FILENO, empty_field_msg, sizeof(empty_field_msg)-1);
        exit(ARGS_ERROR);
    }
    switch (oper) {
        case ADD:
            fd = dirty_open(file_nm, O_RDWR | O_CREAT, 0666);
            status = add(field, fd);
            break;
        case QUERY:
            fd = dirty_open(file_nm, O_RDONLY, WRAP_PERMS);
            status = query(field, fd); /* by default enum is int */
            printf(((status == OK) ? "%u\n" : ""), status);
            break;
        case LIST:
            fd = dirty_open(file_nm, O_RDONLY, WRAP_PERMS);
            status = list(fd);
            break;
        case UNKNOWN:
            write(STDERR_FILENO, commands_msg, sizeof(commands_msg)-1);
            exit(ARGS_ERROR);
            break;
    }
    close(fd);
    if (status == ERR)
        unsopported_file_halt(file_nm);
}

static enum exit_codes add(const char *name, int fd)
{
}

static unsigned int query(const char *name, int fd)
{
}

static exit_codes list(int fd)
{
}

static exit_codes read_one_node(int fd, char buf[FIELD_MAX_SIZE])
{
}

static enum operations get_operation(const char *s)
{
    if (str_case_str(s, "add")) {
        return ADD;
    } else if (str_case_str(s, "query")) {
        return QUERY;
    } else if (str_case_str(s, "list")) {
        return LIST;
    } else {
        return UNKNOWN;
    }
}

static int dirty_open(const char *name, int mode, int perms)
{
    int fd = open(name, mode, perms);
    if (fd < 0) {
        perror(name);
        exit(FILE_ERROR);
    }
    return fd;
}

static void unsopported_file_halt(const char *name)
{
    fprintf(stderr, "%s: unsupported data\n", name);
    exit(FILE_ERROR);
}

static size_t str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r-s;
}

static int str_str(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (!*s1 && !*s2)
            return 1;
    return 0;
}

static int str_n_str(const char *s1, const char *s2, ssize_t size)
{
    for (; size > 0 && *s1 == *s2; s1++, s2++, size--)
        if (!*s1 && !*s2)
            return 1;
    return (size == 0) ? 1 : 0;
}

#define TO_LOWER(c) (((c)>='A' && (c)<='Z') ? (c)-'A' + 'a' : (c))
static int str_case_str(const char *s1, const char *s2)
{
    for (; TO_LOWER(*s1) == TO_LOWER(*s2); s1++, s2++)
        if (!*s1 && !*s2)
            return 1;
    return 0;
}
