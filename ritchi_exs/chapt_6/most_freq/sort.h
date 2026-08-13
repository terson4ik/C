#ifndef MY_SORT_H
#define MY_SORT_H

#include "tree.h" /* give word_arr */

enum orders { DOWN = 1, UP = -1 };

void quick_sort(word_count v[], int left, int right, enum orders order);
void shell_sort(word_count v[], int size, enum orders order);

#endif
