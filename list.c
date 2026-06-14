#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main(void)
{
    struct node *f;
    int tmp_i;
    f = NULL;
    /* 1 2 3 4 -> 4 3 2 1. add to start */
    /* reading and create new nodes */
    while((1 == scanf("%d", &tmp_i))) {
        struct node *t;
        t = malloc(sizeof(*t));
        t->data = tmp_i;
        t->next = f;
        f = t;
    }
    /* writing and delete all nodes */
    printf("outputs:");
    while(f) {
        struct node *t;
        t = f;
        printf(" %d", f->data);
        f = f->next;
        free(t);
    }
    putchar('\n');

    return 0;
}
