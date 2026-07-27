#include <stdio.h> 

void quick_sort(int v[], int left, int right);
void init_321(int v[], int size);
void print_arr(int v[], int size);
void swap(int v[], int i, int j);

#define MAX_LEN 31
int main(int argc, char **argv)
{
    int arr[MAX_LEN];

    init_321(arr, MAX_LEN);
    puts("before:\n");
    print_arr(arr, MAX_LEN);
    quick_sort(arr, 0, MAX_LEN - 1);
    puts("after:\n");
    print_arr(arr, MAX_LEN);
    return 0;
}

void quick_sort(int v[], int left, int right)
{
    int last, i;
    
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;

    for (i = last + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    quick_sort(v, left, last - 1);
    quick_sort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void init_321(int v[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        v[i] = size - i;
}
void print_arr(int v[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("v[%d]\t=%d\n", i, v[i]);
}
