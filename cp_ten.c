#include <stdio.h>

int main(int argc, char **argv)
{
    int c, lcnt;
    FILE *from, *to;
    if(argc < 3) {
        fprintf(stderr, "too few arguments\n");
        return 1;
    }
    from = fopen(argv[1], "r");
    if(!from) {
        perror(argv[1]);
        return 2;
    }
    to = fopen(argv[2], "w");
    if(!to) {
        fclose(from);
        perror(argv[2]);
        return 3;
    }

    while((c = fgetc(from)) != EOF) {
        fputc(c, to);
        if(c == '\n') {
            ++lcnt;
            if(lcnt >= 10)
                break;
        }
    }
    fclose(from);
    fclose(to);
    return 0;
}
