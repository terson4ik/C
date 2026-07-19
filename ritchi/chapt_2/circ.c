#include <stdio.h>

#define SIZE    31
int main()
{
    int arr[SIZE];
    int i, n;
    n = 1;
    printf("You have %d item%s\n", n, (n == 1) ? "" : "s"); 
    n = 5;
    printf("You have %d item%s\n", n, (n == 1) ? "" : "s"); 

    for (i = 0; i < SIZE; i++)
        arr[i] = i + 1;

    for (i = 0; i < SIZE; i++)
        printf("%6d%c", arr[i], (i % 10 == 9 || i + 1 == SIZE) ? '\n' : ' ');
}
