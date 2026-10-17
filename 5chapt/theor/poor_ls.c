#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    DIR *dir;
    struct dirent *dent;

    char *name = (argc > 1) ? argv[1] : ".";
    dir = opendir(name);
    if (!dir) {
        perror(name);
        return 1;
    }

    while ((dent = readdir(dir)) != NULL)
        printf("%s\n", dent->d_name);

    closedir(dir);
    return 0;
}
