#include <stdio.h>
#include <stdlib.h> /* access to getenv */
#include <unistd.h>
#include <sys/wait.h>
#include "shell_engine.h"
#include "my_string.h"
#include "vector.h"

static int cd(char **argv);

int run_command(char **argv)
{
    int pid;
    if (mstrcmp("cd", *argv) == 0)
        return cd(argv);

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

static int cd(char **argv)
{
    char *path;
    if (argv[1]) {
        vector *tilda;
        path = argv[1];
    } else {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "cd: I don't know where's you home :-(\n");
            return -1;
        }
    }
    if (chdir(argv[1]) == -1) {
        perror(path);
        return -1;
    }

    return 0;
}
