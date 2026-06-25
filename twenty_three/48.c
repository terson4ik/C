#include <stdio.h>
#include <stdlib.h>

unsigned int str_size(const char *src)
{
    const char *tmp = src;
    for(; *tmp; ++tmp) {
    }
    return tmp - src;
}

#define SIZE_OF_BUF 4096
int main(int argc, char **argv)
{
    FILE *f_src;
    char *buf;
    unsigned int nl;

    if(argc < 2) {
        f_src = stdin;
    } else {
        f_src = fopen(argv[1], "r");
        if(!f_src) {
            perror(argv[1]);
            return 2;
        }
    }

    buf = malloc(SIZE_OF_BUF);
    if(!buf) {
        perror("fail in memory allocation");
        return 3;
    }

    nl = 0;
    while(fgets(buf, SIZE_OF_BUF, f_src)) {
        unsigned int len = str_size(buf);
        if(buf[len - 1] == '\n')
            ++nl;
    } 
    printf("%u\n", nl);
    free(buf);
    fclose(f_src);

    return 0;
}
