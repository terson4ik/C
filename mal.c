#include <stdio.h>
#include <stdlib.h>

void put(int *a, int size) {
    int i;
    for(i = 0; i < size; i++)
        *(a + i) = i;
}

int main() {
    int *p;
    int size = 100;
    int i;
    p = malloc(sizeof(int) * size);
    if(p == NULL)
        return 1;
    put(p, size);
    for(i = 0; i < size; i++) {
        printf("%d\n", *(p + i));
    }
    free(p);
    return 0;
}
