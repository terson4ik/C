#define _LARGEFILE64_SOURCE
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    off64_t size;
    int fd;

    if (argc < 2) {
        char msg[] = "No file specified.\n";
        write(2, msg, sizeof(msg)-1);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror(argv[1]);
        return 2;
    }

    size = lseek64(fd, 0, SEEK_END);
    if (size < 0) {
        perror("lseek");
        return 3;
    }
    close(fd);

    printf("%lld\n", size);
    return 0;
}

