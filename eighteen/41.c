#include <stdio.h>
#include <stdlib.h>

struct node {
    long x;
    unsigned count;
    struct node *next;
};
/* public API */
void push(struct node **ptr, long num);
void print_freq(const struct node *ptr);
void delete_l(struct node *ptr);
int main(void)
{
    long inp;
    int diagnost;
    struct node *f = NULL;
    while(1 == (diagnost = scanf("%ld ", &inp)))
        push(&f, inp);
    if(diagnost < EOF) {
        perror("INVALID INPUT");
        return 111;
    }
    print_freq(f);
    delete_l(f);
    return 0;
}

/*support function */
struct node *find(struct node **pptr, long target)
{
    struct node *last;
    if(*pptr == NULL)
        return NULL;
                /* firstly get last node */
    for(; (*pptr); last = *pptr, *pptr = (*pptr)->next)
        if((*pptr)->x == target)
            return (*pptr);
    (*pptr) = last;
    return NULL;
}
/*also support function */
int find_max_count(const struct node *ptr)
{
    int max = 1; /* by default */
    while(ptr) {
        if(max < ptr->count)
            max = ptr->count;
        ptr = ptr->next;
    }
    return max;
}

/* finds the end itself during the enumeration, last pointer not needed */
void push(struct node **ptr, long num)
{
    struct node *last = *ptr, *tmp = find(&last, num);
    if(tmp) {
        ++tmp->count;
        return;
    }
    if(last) {
        last->next = malloc(sizeof(struct node));
        last->next->x = num;
        last->next->count = 1;
        last->next->next = NULL;
    } else { /* else -- init new list */
        (*ptr) = malloc(sizeof(struct node));
        (*ptr)->x = num;
        (*ptr)->count = 1;
        (*ptr)->next = NULL;
    }
}

void print_freq(const struct node *ptr)
{
    int max = find_max_count(ptr);
    while(ptr) {
        if(ptr->count == max)
                  /* same formatting using in program 'wc' */
            printf(" %ld", ptr->x);
        ptr = ptr->next;
    }
    putchar('\n');
}

void delete_l(struct node *ptr)
{
    while(ptr) {
        struct node *cur = ptr;
        ptr = ptr->next;
        free(cur);
    }
}
