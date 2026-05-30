#include <stdio.h>

int main(int argc, char **argv)
{
    printf("my name is %s\n", *argv);
    /*
    char **p;
    for(p = argv + 1; *p; p++)
        printf("[%s]\n", *p);
    */
    /*
    int i;
    for(i = 1; i < argc; i++) {
        printf("[%s]\n", *(argv + i));
    }
    */
    return 0;
}
