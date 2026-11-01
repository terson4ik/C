#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int pid, status;
    
    pid = fork();
    if (pid == 1) {
        perror("fork");
        return 127;
    }
    if (pid == 0) {
        int fd = open("flist.txt", O_CREAT| O_WRONLY| O_TRUNC, 0666);
        if (fd == -1) {
            perror("flist.txt");
            return 1;
        }
        dup2(fd, 1);
        close(fd);
        execlp("ls", "ls", "-alR", NULL);
        perror("ls");
        exit(1);
    }
    wait(&status);

    if (!WIFEXITED(status) || WEXITSTATUS(status) !=0) {
        /* handling errors */
    }

    return 0;
}
