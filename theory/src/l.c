#include <stdio.h>
#include <stdlib.h>

struct item {
    int data;
    struct item *next;
};

struct item *int_array_to_list(const int *arr, int len)
{
    struct item *first = NULL, *last = NULL, *tmp;
    int i;
    for(i = 0; i < len; i++) {
        tmp = malloc(sizeof(struct item));
        tmp->data = arr[i];
        tmp->next = NULL;
        if(last)
            last->next = tmp;
        else
            first = tmp;
        last = tmp;
    }
    return first;
}

struct item *int_array_to_list2(const int *arr, int len)
{
    struct item *first = NULL, *tmp;
    int i;
    for(i = len - 1; i >= 0; i--) {
        tmp = malloc(sizeof(*tmp));
        tmp->data = arr[i];
        tmp->next = first;
        first = tmp;
    }
    return first;
}

struct item *int_array_to_list3(const int *arr, int len)
{
    struct item *tmp;
    if(!len)
        return NULL;
    tmp = malloc(sizeof(*tmp));
    tmp->data = *arr;
    tmp->next = int_array_to_list3(arr + 1, len - 1);
    return tmp;
}


void print_and_del(struct item *f)
{
    while(f) {
        struct item *t;
        t = f;
        printf("%d ", f->data);
        f = f->next;
        free(t);
    }
    printf("\n");
}

int list_sum(const struct item *lst)
{
    int sum = 0;
    const struct item *tmp = lst;
    while(tmp) {
        sum += tmp->data;
        tmp = tmp->next;
    }
    return sum;
}

int list_sum2(const struct item *lst)
{
    int sum = 0;
    for(; lst; lst = lst->next)
        sum += lst->data;
    return sum;
}

int list_sum3(const struct item *lst)
{
    if(lst)
        return lst->data + list_sum(lst->next);
    else
        return 0;
}

int list_sum4(const struct item *lst)
{
    return lst ? lst->data + list_sum4(lst->next) : 0;
}

void delete_int_list(struct item *lst)
{
    if(lst) {
        delete_int_list(lst->next);
        free(lst);
    }
}
void rm_neg(struct item **ptr)
{
    while(*ptr) {
        if((*ptr)->data < 0) {
            struct item *tmp = *ptr;
            *ptr = (*ptr)->next;
            free(tmp);
        } else 
            ptr = &(*ptr)->next;
    }
}

void rm_neg2(struct item **ptr)
{
    if(!*ptr)
        return;
    rm_neg2(&(*ptr)->next);
    if((*ptr)->data < 0) {
        struct item *tmp = *ptr;
        *ptr = (*ptr)->next;
        free(tmp);
    }
}

#define MAX 5
int main()
{
    int arr[MAX] = { -1, 2, -3, 4, 5 };
    struct item *f = int_array_to_list(arr, MAX);
    print_and_del(f);
    f = int_array_to_list2(arr, MAX);
    print_and_del(f);
    f = int_array_to_list3(arr, MAX);
    print_and_del(f);
    f = int_array_to_list3(arr, MAX);
    rm_neg2(&f);
    print_and_del(f);
    return 0;
}
