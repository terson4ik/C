#ifndef QUIC_SORT_MY
#define QUIC_SORT_MY

enum orders { DEFAULT = 1, REVERSE = -1 };

void quick_sort(void *lineptr[], int left, int right, 
                int (*comp)(void *, void *), enum orders order);
void quick_sort_word(void *lineptr[], int left, int right, 
                int (*comp)(void *, void *), enum orders order, int pos_word);
#endif