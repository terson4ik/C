#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
static size_t count_nl(const char *s, int size);

int main(int argc, char **argv)
{
    enum { BUF_SIZE = 4096 };
    char buf[BUF_SIZE];
    size_t nl;
    int fd, reads;

    fd = (argc < 2) ? STDIN_FILENO : open(argv[1], O_RDONLY);

    if (fd < 0) {
        perror(argv[1]);
        return 1;
    }

    nl = 0;
    while ((reads = read(fd, buf, BUF_SIZE)) > 0) {
        nl += count_nl(buf, reads);
    }

    if (reads < 0) {
        char msg[] = "Error in std input\n";
        write(STDERR_FILENO, msg, sizeof(msg)-1);
        return 2;
    }

    close(fd);
    printf("%ld\n", nl);
    return 0;
}

static size_t count_nl(const char *s, int size)
{
    size_t akum;
    int i;
    for (i = size, akum = 0; i > 0; i--, s++)
        if (*s == '\n')
            akum++;
    return akum;
}
