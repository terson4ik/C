#include <stdio.h>
#include <stdlib.h>

struct item {
    int x;
    struct item *next;
};

/* chapter a) */
struct item *arr_to_lst(const int arr[], int size)
{
    if(size) {
        struct item *first = malloc(sizeof(struct item));
        first->x = *arr;
        first->next = arr_to_lst(arr + 1, size - 1);
        return first;
    } else {
        return NULL;
    }
}

/* chapter b) */
void recurs_engine(int arr[], int index, const struct item *lst);
int size_lst(const struct item *ptr);
/* this function is wrapper */
int *lst_to_arr(const struct item *lst)
{
    int size = size_lst(lst);
    int *arr = malloc(sizeof(int) * (size + 1));
    arr[0] = size;
    recurs_engine(arr, 1, lst);
    return arr;
}

void recurs_engine(int arr[], int index, const struct item *lst)
{
    if(lst) {
        arr[index] = lst->x;
        recurs_engine(arr, index + 1, lst->next);
    }
}

int size_lst(const struct item *ptr)
{
    return (ptr)? 1 + size_lst(ptr->next) : 0;
}

/* support functions */
void del_lst(struct item *ptr)
{
    if(ptr) {
        del_lst(ptr->next);
        free(ptr);
    }
}

void print_lst(struct item *ptr)
{
    if(ptr) {
        printf("%d ", ptr->x);
        print_lst(ptr->next);
    } else
        putchar('\n');
}

void p_arr(const int arr[], int ind, int max);
/* this function is wrapper */
void print_arr(const int arr[])
{
    p_arr(arr, 1, arr[0] + 1);
}

void p_arr(const int arr[], int ind, int max)
{
    if(ind < max) {
        printf("%d ", arr[ind]);
        p_arr(arr, ind + 1, max);
    } else
        putchar('\n');
}

#define SIZE    5
int main()
{
    int arr[SIZE] = { 1, 2, 3, 4, 5 };
    struct item *f = arr_to_lst(arr, SIZE);
    int *darr = lst_to_arr(f);
    print_arr(darr);
    print_lst(f);
    del_lst(f);
    free(darr);
    return 0;
}
