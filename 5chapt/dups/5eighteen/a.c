/* a) writing to a target file*/
/* in a) and b) dup2 without of child for experiment */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int status, pid, fd, save1fd;
    if (argc < 3) {
        fputs("Usage: run FILE CMDARGS\n", stderr);
        return 1;
    }

    fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (fd == -1) {
        perror(argv[1]);
        return 2;
    }

    save1fd = dup(1);
    dup2(fd, 1);
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
        fprintf(stderr, "command %s have exit code %d\n", argv[2], status);
        return 1;
    }

    dup2(save1fd, 1);
    close(save1fd);
    printf("stdout work correctly\n");
    return 0;
}
