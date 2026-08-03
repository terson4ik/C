#include "quick_sort.h"
#include "my_string.h"

#define ULTIMATIVE_SIZE 500

static void swap (void *v[], int i, int j)
{
    void *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void quick_sort(void *v[], int left, int right, 
                int (*comp)(void *, void *), enum orders order)
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) * order < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quick_sort(v, left, last - 1, comp, order);
    quick_sort(v, last + 1, right, comp, order);
}

void quick_sort_word(void *v[], int left, int right, 
                int (*comp)(void *, void *), enum orders order, int pos_word)
{
    int last, i;
    char left_fild[ULTIMATIVE_SIZE];

    if (left >= right)
        return;
    swap (v, left, (left + right) / 2);
    last = left;
    extract_fild(left_fild, (const char *)v[left], pos_word);
    for (i = left + 1; i <= right; i++) {
        char i_fild[ULTIMATIVE_SIZE]; 
        extract_fild(i_fild, (const char *)v[i], pos_word);
        if ((*comp)(i_fild, left_fild) * order < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    quick_sort_word(v, left, last - 1, comp, order, pos_word);
    quick_sort_word(v, last + 1, right, comp, order, pos_word);
}