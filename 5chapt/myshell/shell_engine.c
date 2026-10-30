#include <stdio.h>
#include <stdlib.h> /* access to getenv */
#include <unistd.h>
#include <sys/wait.h>
#include "shell_engine.h"
#include "my_string.h"
#include "vector.h"

static int cd(char **argv);
static char *cd_path_helper(char *target, int go_home, char *home);

int shell_run_command(char **argv, int in_bg)
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

    if (in_bg) {
        shell_clear_zombies();
    } else {
        int p;
        while ((p = wait(NULL)) != pid && p != -1)
        {}
    }
    return 0;
}

void shell_clear_zombies(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {}
}

static int cd(char **argv)
{
    char *path;
    if (argv[1] == NULL)
        path = cd_path_helper(NULL, 1, getenv("HOME"));
    else if (argv[1][0] == '~') 
        path = cd_path_helper(&argv[1][0], 1, getenv("HOME"));
    else
        path = cd_path_helper(argv[1], 0, NULL);

    if (!path)
        return -1;

    if (chdir(path) == -1) {
        perror(path);
        free(path);
        return -1;
    }

    free(path);
    return 0;
}

static char *cd_path_helper(char *target, int go_home, char *home)
{
    char *reslt;
    vector *vdst = vector_init(255);
    if (!vdst)
        return NULL;

    if(go_home) {
        if (!home) {
            fprintf(stderr, "cd: I don't know where's you home :-(\n");
            vector_dispose(vdst);
            return NULL;
        }
        vector_push_str(vdst, home);

        if (target && target[0] == '~') {
            int indent = 1;
            if (target[1] == '/')
                indent++;
            vector_push_c(vdst, '/');
            vector_push_str(vdst, target+indent);
        }
    } else {
        vector_push_str(vdst, target);
    }

    reslt = mstrdup(vector_get_str(vdst));
    vector_dispose(vdst);
    return reslt;
}
