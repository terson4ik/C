#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    int pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) { /* the child */
        execlp("ls", "ls", "-l", "-a", "/var", NULL);
        perror("ls");
        exit(1);
    }
    wait(NULL);

    printf("Ok\n");

    return 0;
}
