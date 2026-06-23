#include <stdio.h>
#include <stdlib.h>
//#define REVERSE_OUTPUT

struct item {
    int x;
    struct item *next;
};
typedef struct item list;

int module(int num);
/*expected which empty list have NULL pointer */
void l_push(list **ptr_l, int n);
void l_print_all(list *l);
void l_free(list **ptr_l);
#ifndef REVERSE_OUTPUT
void l_reverse(list **ptr_l);
#endif

int main(void)
{
    enum statetes_input {
        FIRST,
        WAIT,
        SECOND,
    } state_io = FIRST;
    int diagnost, num, first, second;
    list *f = NULL;

    while(1 == (diagnost = scanf("%d", &num)))
        /* if f - s <= 5 then push f and s to list */
        if(state_io != FIRST) { /* using enum because it is reliable */
            second = num;
            if(module(first - second) <= 5) {
                /* using stack because it easy to build */
#ifndef REVERSE_OUTPUT
                l_push(&f, first);
                l_push(&f, second);
#else
                l_push(&f, second);
                l_push(&f, first);
#endif
                state_io = SECOND;
            }
            first = second;
        } else {
            first = num;
            state_io = WAIT;
        }

    if(diagnost != EOF) {
        perror("Invalid input");
        l_free(&f);
        return 55;
    }

#ifndef REVERSE_OUTPUT
    l_reverse(&f);
#endif
    if(state_io == SECOND)
        l_print_all(f);

    l_free(&f);
    return 0;
}

int module(int num)
{
    return num > 0 ? num : (~num) + 1;
}

void l_push(list **ptr_l, int n)
{ /*expected which empty list have NULL pointer */
    list *tmp_l = malloc(sizeof(list));
    tmp_l->x = n;
    tmp_l->next = (*ptr_l);
    *ptr_l = tmp_l;
}

void l_print_all(list *l)
{
    char counter = 0;

    while(l) {
        ++counter;
        if(counter == 1)
            printf("%d ", l->x);
        else {
            printf("%d\n", l->x);
            counter = 0;
        }
        l = l->next;
    }
}

void l_free(list **ptr_l)
{
    while(*ptr_l) {
        list *cur = *ptr_l;
        *ptr_l = (*ptr_l)->next;
        free(cur);
    }
}

#ifndef REVERSE_OUTPUT
void l_reverse(list **ptr_l)
{
    list *l_next;

    if(!*ptr_l)
        return; /* nothing to do */

    l_next = (*ptr_l)->next;
    (*ptr_l)->next = NULL;
    while(l_next) { /* 1->2->3 | 2->1->3 | 3->2->1 */
        list *tmp = l_next->next;
        l_next->next = (*ptr_l);
        (*ptr_l) = l_next;
        l_next = tmp;
    }
}
#endif
