#include <stdio.h>
#include <stdlib.h> /* access to getenv */
#include <unistd.h>
#include <sys/wait.h>
#include "shell_engine.h"
#include "my_string.h"

int run_command(char **argv)
{
    int pid;
    if (mstrcmp("cd", *argv) == 0) {
        char *path = (argv[1]) ? argv[1] : getenv("HOME");
        if (!path) {
            fprintf(stderr, "%s: unknown path\n");
            return -1;
        }

        if (chdir(path) == -1) {
            perror(path);
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
