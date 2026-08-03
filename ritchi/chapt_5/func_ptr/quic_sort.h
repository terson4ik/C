#ifndef QUIC_SORT_MY
#define QUIC_SORT_MY

void quic_sort(void *lineptr[], int left, int right, 
                int (*comp)(void *, void *));

#endif