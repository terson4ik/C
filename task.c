#include <stdlib.h>

int *create_array(int size) {
    return malloc(sizeof(int) * size);
}

int main() {
    int s = 10;
    int* arr = create_array(s);
    return 0;
}
