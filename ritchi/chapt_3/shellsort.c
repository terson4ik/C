#include <stdio.h>

void shellsort(int v[], int n);
void print_arr(int v[], int n);

int main()
{
    int arr[] = { 2, 99, 554, 11, 44, 1, 5, 0 };

    print_arr(arr, sizeof(arr) / sizeof(int));
    shellsort(arr, sizeof(arr) / sizeof(int));
    print_arr(arr, sizeof(arr) / sizeof(int));
    return 0;
}
void print_arr(int v[], int n)
{
    int i;
    
    for (i = 0; i < n; i++)
        printf("%d%c", v[i], (i + 1 == n) ? '\n' : ' ');
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && v[j]>v[j+gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}
