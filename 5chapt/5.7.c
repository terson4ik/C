#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
static unsigned int str_len(const char *s);
static int str_str(const char *s1, const char *s2);
static int str_n_str(const char *s1, const char *s2, ssize_t size);
static void str_n_cpy(char *dst, const char *src, ssize_t size);
static void dirty_mem_cpy(void *dest, const void *src, ssize_t size);


enum { STR_SIZE = 60, ONE_FIELD = 64 }; /* 60+int */
enum operations { ADD, QUERY, LIST, ERROR };

static enum operations get_operation(const char *s);
static void handling_operator(const char *operator,
                              const char *file, const char *field);
static int node_add(const char name[STR_SIZE], int fd);
static int field_new(const char name[STR_SIZE], int fd);
static int node_query(const char name[STR_SIZE], int fd);
static int node_list(int fd);
static int danger_open(const char *name, int mode, int perms);
static void invalid_data_halt(const char *file_name);


static const char no_args_msg[] = "Usage: bd FILE COMMAND [FIELD_NAME]\n";
static const char list_opers_msg[] = "Available operations: add, query, list\n";
static const char empty_field_msg[] = "No field specified\n";
int main(int argc, char **argv)
{
    if (argc < 3) { /* 2 */
        write(STDERR_FILENO, no_args_msg, sizeof(no_args_msg)-1);
        return 1;
    }

    if(argv[3] && str_len(argv[3]) >= STR_SIZE) {
        fprintf(stderr, "Supported size of name of the field: %d\n", STR_SIZE);
        return 3;
    }

    handling_operator(argv[2], argv[1], argv[3]);
    return 0;
}

static enum operations get_operation(const char *s)
{
    if (str_str(s, "add"))
        return ADD;
    else if (str_str(s, "query"))
        return QUERY;
    else if (str_str(s, "list"))
        return LIST;
    else
        return ERROR;
}
static void handling_operator(const char *operator,
                              const char *file, const char *field)
{
    enum operations oper = get_operation(operator);
    int fd, exit_status;
    if (oper != LIST && !field) {
        write(STDERR_FILENO, empty_field_msg, sizeof(empty_field_msg)-1);
        exit(2);
    } 
    switch (oper) {
        case ADD:
            fd = danger_open(file, O_RDWR | O_CREAT, 0666);
            exit_status = node_add(field, fd);
            if (exit_status < 0)
                invalid_data_halt(file);
            break;
        case QUERY:
            fd = danger_open(file, O_RDONLY, 0);
            exit_status = node_query(field, fd);
            if (exit_status < 0)
                invalid_data_halt(file);
            printf("%u\n", exit_status);
            break;
        case LIST:
            fd = danger_open(file, O_RDONLY, 0);
            exit_status = node_list(fd);
            if (exit_status < 0)
                invalid_data_halt(file);
            break;
        default:
        case ERROR:
            fprintf(stderr, "%s: unknown operation\n%s", operator, list_opers_msg);
            exit(4);
    }
    close(fd);
}

static int node_add(const char name[STR_SIZE], int fd)
{
    char buf[ONE_FIELD];
    int count;
    while ((count = read(fd, buf, ONE_FIELD)) > 0) {
        if (count < ONE_FIELD)
            return -1;

        if (str_n_str(buf, name, STR_SIZE)) {
            int new_val;
            dirty_mem_cpy(&new_val, buf+STR_SIZE, sizeof(int));
            new_val++;
            lseek(fd, -sizeof(int), SEEK_CUR); /* in linux don't use lseek64() */
            count = write(fd, &new_val, sizeof(int));
            if (count != 4)
                return 0;
            return 1;
        }
    }
    if (count < 0)
        return -1;
    
    return field_new(name, fd);
}

static int field_new(const char name[STR_SIZE], int fd)
{
    int count;
    char buf[ONE_FIELD];
    str_n_cpy(buf, name, STR_SIZE);
    count = 1;
    dirty_mem_cpy(buf+STR_SIZE, &count, sizeof(int));
    count = write(fd, buf, ONE_FIELD);
    return (count == ONE_FIELD) ? 1 : 0;
}

static int node_query(const char name[STR_SIZE], int fd)
{
    char buf[ONE_FIELD];
    int count;
    while ((count = read(fd, buf, ONE_FIELD)) > 0) {
        if (count < ONE_FIELD)
            return -1;

        if (str_n_str(buf, name, STR_SIZE)) {
            int res;
            dirty_mem_cpy(&res, buf+STR_SIZE, sizeof(int));
            return res;
        }
    }
    return 0;
}

static int node_list(int fd)
{
    char buf[ONE_FIELD];
    int count, val;
    while ((count = read(fd, buf, ONE_FIELD)) > 0) {
        if (count < ONE_FIELD)
            return -1;

        dirty_mem_cpy(&val, buf+STR_SIZE, sizeof(int));
        printf("%s: %u\n", buf, val);
    }
    return 1;
}

static int danger_open(const char *name, int mode, int perms)
{
    int fd = open(name, mode, perms);
    if (fd < 0) {
        perror(name);
        exit(5);
    }
    return fd;
}

static unsigned int str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r-s;
}

static int str_str(const char *s1, const char *s2)
{
    for ( ; *s1==*s2; s1++, s2++)
        if (!*s1 && !*s2)
            return 1;
    return 0;
}

static int str_n_str(const char *s1, const char *s2, ssize_t size)
{
    for ( ; size > 0 && *s1==*s2; s1++, s2++, size--)
        if (!*s1 && !*s2)
            return 1;
    return 0;
}

static void str_n_cpy(char *dst, const char *src, ssize_t size)
{
    while (size-- > 0 && (*dst++ = *src++))
    {}

    while (size-- > 0)
        *dst++ = '\0';
}

static void dirty_mem_cpy(void *m1, const void *m2, ssize_t size)
{
    const char *src = m2;
    char *dst = m1;
    while (size-- > 0)
        *dst++ = *src++;
}

static void invalid_data_halt(const char *file_name)
{
    fprintf(stderr, "%s: unsupported data", file_name);
    exit(5);
}
