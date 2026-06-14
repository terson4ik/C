#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main(void)
{
    struct node *f, *l;
    int tmp_i;
    f = l = NULL;
    /*1 2 3 -> 1 2 3; add to tail. Second ptr need */
    while(1 == scanf("%d", &tmp_i)) {
        struct node *t;
        t = malloc(sizeof(*t));
        t->data = tmp_i;
        t->next = NULL;
        if(!f) {
            l = f = t;
        } else {
            l->next = t;
            l = t;
        }
    }
    while(f) {
        struct node *t;
        t = f;
        printf(" %d,", f->data);
        f = f->next;
        free(t);
    }
    return 0;
}
