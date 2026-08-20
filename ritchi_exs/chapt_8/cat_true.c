/* 8.1: cat */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void rav_file_cp(int fdsrc, int fddst);
int main(int argc, char **argv)
{
    if (argc == 1)
        rav_file_cp(0, 1);
    else
        while (*++argv) {
            int fsrc = open(*argv, O_RDONLY, 0);
            if (fsrc != -1) {
                rav_file_cp(fsrc, 1);
                close(fsrc);
            } else {
                perror(*argv);
                return 1;
            }
        }
    return 0;
}

void rav_file_cp(int fdsrc, int fddst)
{
    char buf[BUFSIZ];
    int nb;
    while ((nb = read(fdsrc, buf, BUFSIZ)) > 0)
        if (write(fddst, buf, nb) != nb) {
            perror("In writing");
            exit(2);
        }
}
