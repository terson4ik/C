#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int run_command(char **argv)
{
    for (; *argv; argv++)
        printf("[%s]\n", *argv);
    return 0;
}
