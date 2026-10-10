#define _LARGEFILE64_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
static size_t a_to_ulong(const char *s);
static int is_num(const char *s);

int main(int argc, char **argv)
{
    enum { BUF_SIZE = 4096 };
    int fd;
    size_t len;
    char val;
    char buf[BUF_SIZE];

    if (argc < 5) { /* 4 needed */
        char msg[] = "Usage: prog <name.txt> <start_pos> <length> <value>\n";
        write(STDERR_FILENO, msg, sizeof(msg)-1);
        return 1;
    }
    if (!is_num(argv[2]) || !is_num(argv[3]) || !is_num(argv[4])) {
        char msg[] = "Incorrect argument: it's not a number!\n";
        write(STDERR_FILENO, msg, sizeof(msg)-1);
        return 2;
    }

    fd = open(argv[1], O_WRONLY);
    if (fd < 0) {
        perror(argv[1]);
        return 2;
    }

    lseek64(fd, a_to_ulong(argv[2]), SEEK_SET);
    len = a_to_ulong(argv[3]);
    val = a_to_ulong(argv[4]);
    if (val > CHAR_MAX) {
        fprintf(stderr, "%d out of range %d", val, CHAR_MAX);
        return 3;
    }

    memset(buf, val, (len > BUF_SIZE) ? BUF_SIZE : len);
    while (len > 0) {
        int writed, count, shift;
        count = (len > BUF_SIZE) ? BUF_SIZE : len;
        len -= count;
        shift = 0;
        while (shift < count) {
            writed = write(fd, buf, count-shift);
            shift += writed;
        } 
    }
    close(fd);
    return 0;
}

static size_t a_to_ulong(const char *s)
{
    size_t res;
    for (res = 0; *s; s++)
        res = res*10 + *s-'0';
    return res;
}

static int is_num(const char *s)
{
    for ( ; *s; s++)
        if (!isdigit(*s))
            return 0;
    return 1;
}
