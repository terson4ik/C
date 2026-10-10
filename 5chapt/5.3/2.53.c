#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
size_t str_len(const char *s);

int main(int argc, char **argv)
{
    enum { BUFF_SIZE = 4096 };
    FILE *source, *spaces;
    char buf[BUFF_SIZE];
    int fd_lengths;
    int len;

    if (argc < 4) {
        fputs("Usage: prog <src.txt> <spaces.txt> <lengths.bin>\n", stderr);
        return 1;
    }
    
    source = fopen(argv[1], "r");
    if (!source) {
        perror(argv[1]);
        return 1;
    }

    spaces = fopen(argv[2], "w");
    if (!spaces) {
        perror(argv[2]);
        /* source FILE* will automatically closed */
        return 2;
    }

    fd_lengths = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (fd_lengths < 0) {
        perror(argv[3]);
        /* other file-descriptors will closed automatically */
        return 3;
    }

    while (fgets(buf, BUFF_SIZE, source)) {
        char is_space;

        len = str_len(buf);
        if (buf[0] == ' ') {
            fputs(buf, spaces);
            is_space = 1;
        } else {
            is_space = 0;
        }

        while (buf[str_len(buf)-1] != '\n') {
            if (!fgets(buf, BUFF_SIZE, source))
                break;
            if (is_space)
                fputs(buf, spaces);
            len += str_len(buf);
        }
        write(fd_lengths, &len, sizeof(len));
    }
    return 0;
}

size_t str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r-s;
}
