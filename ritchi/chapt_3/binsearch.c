#include <stdio.h>
#include <stdlib.h>

int binsearch(int x, const int v[], int n);
void fill_seq(int v[], int n);
#define SIZE_ARR    100 + 1
int main(int argc, char **argv)
{
    int v[SIZE_ARR];
    int targ;

    if (argc < 2)
        return 1;

    targ = atoi(argv[1]);
    if (targ > SIZE_ARR - 1)
        return 2;

    fill_seq(v, SIZE_ARR);

    printf("\n%d\n", binsearch(targ, v, SIZE_ARR));
    return 0;
}

int binsearch(int x, const int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
void fill_seq(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%-3d%c", (v[i] = i * 2), (i % 10 == 9 || i + 1 == n) ? '\n' 
                                                                   : ' ');
}
