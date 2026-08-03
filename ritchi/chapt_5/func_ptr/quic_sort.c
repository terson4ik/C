#include "quic_sort.h"
static void swap (void *v[], int i, int j)
{
    void *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void quic_sort(void *v[], int left, int right, 
                int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quic_sort(v, left, last - 1, comp);
    quic_sort(v, last + 1, right, comp);
}
