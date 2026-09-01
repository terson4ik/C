#include <stdio.h>

double dbl_sum(const double *a, int size)
{
    return size > 0 ? *a + dbl_sum(a+1, size-1) : 0;
}

double dbl_min(const double *a, int size)
{
    double d;
    if (size == 1)
        return *a;
    d = dbl_min(a+1, size-1);
    return *a < d ? *a : d;
}

double dbl_avarage(const double *a, int size)
{
    return dbl_sum(a, size) / (double) size;
}

int is_negative(int x) { return x < 0; }
int is_even(int x) { return x % 2 == 0; }
int is_div7(int x) { return x % 7 == 0; }
void delete_from_list(struct item **pcur, int (*crit)(int))
{
    while(*pcur) {
        if ((*crit)((*pcur)->data)) {
            struct item *tmp = *pcur;
            *pcur = (*pcur)->next;
            free(tmp);
        } else {
            pcur = &(*pcur)->next;
        }
    }
}
int main()
{
    /* It's not a pointer, it's common header:
    double *fn (const double *, int);

    This is function pointer */
    double (*fptr)(const double *, int);   
    double arr[100];
    double res;
    fptr = &dbl_min;
    fptr = dbl_min;
    /* Next is absolutely equivalents: */
    res = (*fptr)(arr, sizeof(arr)/sizeof(*arr));
    res = fptr(arr, sizeof(arr)/sizeof(*arr));
    delete_from_list(&first, &is_negative);
    delete_from_list(&first, &is_div7);

    return 0;
}
