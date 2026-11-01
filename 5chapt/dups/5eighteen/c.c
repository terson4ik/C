/* c) equal of >> in bash 
 * c-d have good tone of dups() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pid, status;
    if (argc < 3) {
        fputs("Usage: run FILE COMMAND\n", stderr);
        return 1;
    }
    
    pid = fork();
    if (pid == -1) {
        perror("fork()");
        return 127;
    }
    if (pid == 0) {
        int fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0666);
        if (fd == -1) {
            perror(argv[1]);
            _exit(5);
        }
        dup2(fd, 1);
        execvp(argv[2], argv+2);
        perror(argv[2]);
        _exit(127);
    }
    
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "command %s with exit code %d", argv[2], status);
        return 3;
    }

    printf("stdout working)))\n");
    return 0;
}
