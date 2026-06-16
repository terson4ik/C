#include <stdio.h>
#include <stdlib.h>

struct item {
    int x;
    struct item *next;
};

/* chapter a) */
struct item *arr_to_lst(int arr[], int len)
{
    struct item *first = NULL;
    int i;
    for(i = len - 1; i >= 0; --i) {
        /* reverse adding allows use stack mechanism to build list
         * without using `last` pointer of list */
        struct item *tmp = malloc(sizeof(*tmp));
        tmp->x = arr[i];
        tmp->next = first; /* at the very beginning, first == NULL */
        first = tmp;
    }
    return first;
}

int size_lst(const struct item *ptr)
{
    int i;
    for(i = 0; ptr; ++i)
        ptr = ptr->next;
    return i;
}

/* chapter b) */
int *lst_to_arr(const struct item *ptr)
{
    int i = size_lst(ptr);
    int j;
    int *arr = malloc((i + 1) * sizeof(int));
    arr[0] = i;
    for(j = 1; j <= i && ptr != NULL; ++j) {
        arr[j] = ptr->x;
        ptr = ptr->next;
    }
    return arr;
}

/* support function */
void destroy_list(struct item *ptr)
{
    while(ptr) {
        struct item *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

/* support function */
void print_lst(const struct item *ptr)
{
    while(ptr) {
        printf("%d ", ptr->x);
        ptr = ptr->next;
    }
    putchar('\n');
}

/* in task condition, arr[0] contain the size of array */
void print_arr(const int *arr)
{
    int i;
    for(i = 1; i <= arr[0]; ++i)
        printf("%d ", arr[i]);
    putchar('\n');
}

#define SIZE    5
int main(void)
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    int *ptr_arr;
    struct item *f = arr_to_lst(arr, SIZE);
    print_lst(f);
    ptr_arr = lst_to_arr(f);
    print_arr(ptr_arr);
    destroy_list(f);
    free(ptr_arr);
    return 0;
}
