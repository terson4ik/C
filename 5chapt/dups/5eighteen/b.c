/* b) read from the file 
 * for study reason use dup in out of the children*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
    int fd, save0fd, status, pid;
    if (argc < 3) {
        fputs("Usage: run FILE COMMAND ...\n", stderr);
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    save0fd = fcntl(0, F_DUPFD, 0);
    dup2(fd, 0);
    close(fd);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 127;
    }
    if (pid == 0) {
        execvp(argv[2], argv+2);
        perror(argv[2]);
        _exit(127);
    }

    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "command %s exited with error code: %d", argv[2], status);
        return 3;
    }

    dup2(save0fd, 0);
    close(save0fd);

    printf("stdout work correctly\n");
    return 0;
}
