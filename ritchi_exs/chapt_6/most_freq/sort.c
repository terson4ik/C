#include "sort.h"
static void swap(word_count v[], int i, int j);


typedef struct tree_word_tag tree_word;

void quick_sort(word_count v[], int left, int right, enum orders order)
{
    int last, i;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = last + 1; i < right; i++)
        if ((v[left].count - v[i].count) * order > 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quick_sort(v, left, last, order);
    quick_sort(v, last + 1, right, order);
}

void shell_sort(word_count v[], int size, enum orders order)
{
    int gap, i, j;
    for (gap = size / 2; gap > 0; gap /= 2)
        for (i = gap; i < size; i++)
            for (j = i - gap; j >= 0 && (v[j].count - v[j + gap].count) *
                                                        order > 0; j -= gap)
                swap(v, j, j + gap);
}

static void swap(word_count v[], int i, int j)
{
    word_count temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
