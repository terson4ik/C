#include <stdio.h>

void intfilesum(FILE *f, int *sum, int *count)
{
    int n;
    *sum = *count = 0;
    while(1 == fscanf(f, "%d", &n)) {
        *sum += n;
        (*count)++;
    }
}

int main(int argc, char **argv)
{
    FILE *src;
    int sum, cnt;
    if(argc < 2) {
        fprintf(stderr, "too few arguments\n");
        return 1;
    }
    src = fopen(argv[1], "r");
    if(!src) {
        perror(argv[1]);
        return 2;
    }
    intfilesum(src, &sum, &cnt);
    printf("s: %d, count: %d\n", sum, cnt);
    fclose(src);
    return 0;
}
