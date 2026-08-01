#include <stdio.h>

int main(int argc, char *argv[])
{
    while (--argc) /* argc ALWAYS == 1 */
        printf((argc > 1) ? "%s " : "%s", *++argv);
    putchar('\n');
    return 0;
}
