#include <stdio.h>
#include <stdlib.h>

struct node {
    long x;
    int meets;
    struct node *next;
};
struct query {
    struct node *first, *last;
}; /* use query for fast adding to end. It's frequent operation */
typedef struct query *que;

/* this is non standard push: full bypass and inc meets var */
void init_q(que *q);
void push_q(que *q, long num);
void print_filter_meet(const struct node *first, int targ);
void del_q(que *q);
void del_list(struct node *first);

#define TARGET  3
int main(void)
{
    que q = NULL;
    long inp;
    init_q(&q);
    /* in prod, need to check scanf val, but it is study */
    while(1 == scanf("%d", &inp))
        push_q(&q, inp);
    print_filter_meet(q->first, TARGET);
    del_q(&q);
    return 0;
}

void init_q(que *q)
{
    *q = malloc(sizeof(struct query));
    (*q)->last = (*q)->first = NULL;
}

/* support function, denied to use in main function */
struct node *meet(const struct node *ptr, long targ)
{ /* DANGER!!! Using recursive method */
    if(ptr == NULL)
        return NULL;
    return ptr->x == targ ? (struct node *)ptr : meet(ptr->next, targ);
}

void push_q(que *q, long num)
{ /* this is non standard push: full bypass and inc meets var */
    struct node *find = meet((*q)->first, num);
    if(find) {
        ++find->meets;
        return;
    }
    find = malloc(sizeof(struct node));
    find->x = num;
    find->meets = 1;
    find->next = NULL;
    if((*q)->first == NULL)
        (*q)->first = (*q)->last = find;
    else {
        (*q)->last->next = find;
        (*q)->last = find;
    }
}

void print_filter_meet(const struct node *ptr, int targ)
{ /* in this case, recursive method not justified: too hard to implement */
    while(ptr) { /* skip create temporary node -- no reason for this func */
        if(ptr->meets == targ)
            printf("%ld, ", ptr->x);
        ptr = ptr->next;
    }
    putchar('\n');
}

void del_q(que *q)
{
    del_list((*q)->first);
    free(*q); /* no 'q', because we need real address */
}
void del_list(struct node *ptr)
{
    if(!ptr)
        return;
    del_list(ptr->next);
    free(ptr);
}
