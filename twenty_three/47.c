/* Analog of ``cat`` */
#include <stdio.h>
#include <stdlib.h>

FILE *safe_open_read(const char *name)
{
    FILE *src;
    src = fopen(name, "r");
    if(!src) {
        perror(name);
        exit(10);
    }
    return src;
}

#define SIZE_OF_BUFFER  4098
int main(int argc, char **argv)
{
    FILE *src;
    char *buffer;
    int fn;

    buffer = malloc(SIZE_OF_BUFFER);
    if(!buffer) {
        perror("Error in create new buffer");
        return 1;
    }

    fn = 1;
    do {
        long reads_bytes;
        if(argc > 2)
            src = safe_open_read(argv[fn]);
        else
            src = stdin;

        while((reads_bytes = fread(buffer, 1, SIZE_OF_BUFFER, src)))
            fwrite(buffer, 1, reads_bytes, stdout);

        if(!feof(src) && ferror(src))
            exit(2);

        if(src == stdin)
            break;
        else
            fclose(src);

        ++fn;
    } while(fn < argc);

    free(buffer);
    return 0;
}
