#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_BUF 8192
int main(int argc, char **argv)
{
    FILE *f_src;
    char *buf;
    unsigned int nl;
    size_t read_bytes;

    if(argc < 2)
        f_src = stdin;
    else {
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
                /*                 1 byte element. Important signature */
    while((read_bytes = fread(buf, 1, SIZE_OF_BUF, f_src)))
        for(; read_bytes; --read_bytes)
            if(buf[read_bytes - 1] == '\n')
                ++nl;

    printf("%u\n", nl);
    free(buf);
    if(f_src != stdin)
        fclose(f_src);

    return 0;
}
