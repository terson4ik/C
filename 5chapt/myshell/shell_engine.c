#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell_engine.h"
#include "my_string.h"

int run_command(char **argv)
{
    int pid;
    if (mstrcmp("cd", *argv) == 0) {
        if (chdir(argv[1]) == -1) {
            perror(*argv);
            return -1;
        }
        return 0;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    } else
    if (pid == 0) {
        execvp(*argv, argv);
        perror(*argv);
        fflush(stderr);
        _exit(255);
    }
    wait(NULL);
    return 0;
}
