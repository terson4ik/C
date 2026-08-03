#ifndef QUIC_SORT_MY
#define QUIC_SORT_MY

enum orders { DEFAULT = 1, REVERSE = -1 };

void quic_sort(void *lineptr[], int left, int right, 
                int (*comp)(void *, void *), enum orders order);

#endif