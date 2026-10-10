#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define INT_WIDTH 4
int main(int argc, char **argv)
{
    enum { BUFSIZE = 4096 };

    int fd, buf;
    char str[BUFSIZE];

    if (argc < 2) {
        char msg[] = "At least 1 parameters needed\n";
        write(STDERR_FILENO, msg, sizeof(msg)-1);
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror(argv[1]);
        return 1;
    }

    while (fgets(str, BUFSIZE, stdin)) {
        buf = atoi(str);
        write(fd, &buf, INT_WIDTH);
    }

    return 0;
}
