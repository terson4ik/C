#include <stdio.h>
#include <stdlib.h>


void hanoi(int n, int start, int target, int buffer)
{
    if(n == 0)
        return;
    hanoi(n - 1, start, buffer, target);
    printf("%d: %d -> %d\n", n, start, target);
    hanoi(n - 1, buffer, target, start);
}

int main(int argc, char **argv)
{
    int n;
    if(argc < 2) {
        fprintf(stderr, "No parameters given\n");
        return 1;
    }

    n = atoi(argv[1]);
    if(n < 1) {
        fprintf(stderr, "Invalid input(n < 1)\n");
        return 1;
    }

    hanoi(n, 1, 2, 3);

    return 0;
}
