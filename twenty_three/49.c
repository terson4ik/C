/* write data in stdinput to argv[1] file */
#include <stdio.h>
#include <stdlib.h>

/* WARNING!!! Buffer allocate in the stack. Don't set very big value */
#define SIZE_OF_BUF 4096
int main(int argc, char **argv)
{
    FILE *dest;
    char buf[SIZE_OF_BUF];

    if(argc < 2) {
        fprintf(stderr, "Set target to write.\n");
        return 1;
    }

    if((dest = fopen(argv[1], "w")) == NULL) {
        perror(argv[1]);
        return 2;
    }
    
    while(fgets(buf, SIZE_OF_BUF, stdin))
        fputs(buf, dest);

    fclose(dest);
    return 0;
}
