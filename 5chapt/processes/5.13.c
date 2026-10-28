#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SEPARATOR ';'

typedef struct {
    pid_t pid;
    char *name;
} process;

/* malloc cmdlines arguments
 * fill args of argv without ./a.out and ";;"->NULL
 * return count of entry's and malloc process array
 * run all tasks and fill process arr
 * go to handler of waits and if return then check exit code and print this */

int parse_argv(char **argv, char **target_args);
void run_tasks(char **cmdlines, process procs[], int count);
void handling_zombies(process procs[], int count);
static char **get_next_obj(char **vect);
static int is_separator(char *s);
static const char *proc_get_name(process procs[], int pid, int count);

int main(int argc, char **argv)
{
    char **cmdlines;
    process *procs;
    int procs_count;

    if (argc < 2)
        return 0; /* no args no error */

    cmdlines = malloc(argc*sizeof(char**));
    if (!cmdlines) {
        perror("malloc");
        return 1;
    }
    procs_count = parse_argv(argv, cmdlines);
    procs = malloc(procs_count*sizeof(*procs));
    if (!procs) {
        perror("malloc");
        return 2;
    }

    run_tasks(cmdlines, procs, procs_count);
    handling_zombies(procs, procs_count);
    /* heap will automatically disposed by OS */
    return 0;
}

int parse_argv(char **argv, char **target_args)
{
    int count = 0;
    char in = 0;
    while (*(++argv)) {
        if (!in) {
            count++;
            in = 1;
        }

        if (is_separator(*argv)) {
            *(target_args++) = NULL;
            in = 0;
        } else {
            *(target_args++) = *argv;
        }
    }
    *target_args = NULL;

    return count;
}

void run_tasks(char **cmdlines, process procs[], int count)
{
    int i;
    for (i = 0; i < count; i++, cmdlines = get_next_obj(cmdlines)) {
        int pid = fork();
        if (pid == -1) {
            perror("fork");
            procs[i].name = NULL;
            procs[i].pid  = 0; /* impossible pid */
            continue;
        }

        if (pid == 0) {
            execvp(*cmdlines, cmdlines);
            perror(*cmdlines);
            fflush(stderr);
            _exit(127);
        }
        procs[i].pid  = pid;
        procs[i].name = *cmdlines;
    }
}

void handling_zombies(process procs[], int count)
{
    int stat, pid;
    while ((pid = wait(&stat)) != -1)
        if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0)
            printf("\n------\n%s\n------\n", proc_get_name(procs, pid, count));
}

static int is_separator(char *s)
{
    return s[0]==SEPARATOR && s[1]==SEPARATOR && s[2]=='\0';
}

static char **get_next_obj(char **vect)
{
    for (; *vect; vect++)
    {}
    return vect+1;
}

static const char *proc_get_name(process procs[], int pid, int count)
{
    for (count--; count >= 0; count--)
        if (procs[count].pid == pid)
            return procs[count].name;
    return NULL;
}
