#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int stat;
    int pid;
    if (argc < 2) {
        fputs("No arguments yet\n", stderr);
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], argv+1);
        perror(argv[1]);
        fflush(stderr);
        _exit(2);
    }
    wait(&stat);

    printf((WIFEXITED(stat) ? "exited %d\n"     : "killed %d\n"),
            WIFEXITED(stat) ? WEXITSTATUS(stat) : WTERMSIG(stat));

    return 0;
}
