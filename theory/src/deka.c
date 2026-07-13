#include <stdio.h>
#include <stdlib.h>

struct dbl_item {
    double data;
    struct dbl_item *prev, *next;
};

int main()
{
    struct dbl_item *first = NULL, *last = NULL;
    struct dbl_item *current = NULL, *tmp;
    double x = 5.0;
    /* adding to begin deck */
    tmp = malloc(sizeof(struct dbl_item));
    tmp->data = x;
    tmp->prev = NULL;
    tmp->next = first;
    if(first)
        first->prev = tmp;
    else
        last = tmp;
    first = tmp;
    /* adding to end of deck */
    tmp = malloc(sizeof(struct dbl_item));
    tmp->next = NULL;
    tmp->prev = last;
    if(last)
        last->next = tmp;
    else
        first = tmp;
    last = tmp;
    /* popping begin */
    if(first) {
        tmp = first;
        first = first->next;
        if(first) /* if move `if` to `while` then it's remove all deck */
            first->prev = NULL;
        else
            last = NULL;
        free(tmp);
    }
    /* popping end of deck */
    if(last) {
        tmp = last;
        last = last->prev;
        if(last) /* if move `if` to `while` then it's remove all deck */
            last->next = NULL;
        else
            first = NULL;
        free(tmp);
    }
    /* example of clearly removing the deck */
    if(first) {
        first = first->next;
        while(first) {
            free(first->prev);
            first = first->next;
        }
        free(last);
        last = NULL;
    }
    /* example of adding before cur item in deck */
    current = first;
    tmp = malloc(sizeof(struct dbl_item));
    tmp->data = x;
    tmp->next = current;
    tmp->prev = current->prev;
    current->prev = tmp;
    if(tmp->prev)
        tmp->prev->next = tmp;
    else
        first = tmp;
    /* also adding to after cur item in deck */
    tmp = malloc(sizeof(struct dbl_item));
    tmp->data = x;
    tmp->prev = current;
    tmp->next = current->next;
    current->next = tmp;
    if(tmp->next)
        tmp->next->prev = tmp;
    else
        last = tmp;
    /* removing current item */
    if(current->prev)
        current->prev->next = current->next;
    else
        first = current->next;
    if(current->next)
        current->next->prev = current->prev;
    else
        last = current->prev;

    free(current);
    current = NULL;
    /* or */
    tmp = current;
    current = current->next; /* or prev */
    free(tmp);

    return 0;
}
