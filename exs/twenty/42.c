/* reverse order words in string */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE_OF_VECTOR  11
typedef struct teg_item {
    unsigned long vector_size, vector_current_size;
    char *vector;  /* dynamically changes his size */
    struct teg_item *next;
} list;

/* this function automatically initial new list if his empty */
void list_push_char(list **ptr_l, char c);
void list_print_nodes(list *l);
void list_free_memory(list **ptr_l);

int main(void)
{
    list *first = NULL; /* emulate stack */
    int c;

    while((c = getchar()) != EOF) {
        if(c != '\n') {
            list_push_char(&first, c); /* stack mechanism */
        } else if(first) {
            list_print_nodes(first);
            list_free_memory(&first);
        }
    } /* in case when '\n' not detected */
    list_print_nodes(first);
    list_free_memory(&first);

    return 0;
}
void list_init(list **ptr_l);
void arr_push(char **ptr_arr, unsigned long *limit, unsigned long *size, char c);
void list_new_node(list **ptr_l);

void list_push_char(list **ptr_l, char c)
{ /* stack mechanism */
    if(!*ptr_l)
        list_init(ptr_l);

    if(c != ' ' && c != '\t' && c != '\n')
        arr_push(&(*ptr_l)->vector, &(*ptr_l)->vector_size, 
                                    &(*ptr_l)->vector_current_size, c);
    else
        if((*ptr_l)->vector[0] != '\0') {
            list *new_item;
            list_init(&new_item);
            new_item->next = *ptr_l;
            *ptr_l = new_item;
        }
}

void list_init(list **ptr_l)
{
    (*ptr_l) = malloc(sizeof(list));
    if(!*ptr_l) {
        perror("Error in memory allocation for list `list_init`");
        exit(2);
    }

    (*ptr_l)->vector = malloc(DEFAULT_SIZE_OF_VECTOR);
    if(!(*ptr_l)->vector) {
        perror("Error in memory allocation for array `list_init`");
        exit(3);
    }

    (*ptr_l)->vector_size = DEFAULT_SIZE_OF_VECTOR;
    (*ptr_l)->vector_current_size = 0;
    (*ptr_l)->vector[0] = '\0';
    (*ptr_l)->next = NULL;
}

void increase_arr(char **ptr_arr, unsigned long new_size);
void arr_push(char **ptr_arr, unsigned long *limit, unsigned long *size, char c)
{
    if(*size >= *limit - 1) {
        *limit *= 2;
        increase_arr(ptr_arr, *limit);
    }

    (*ptr_arr)[(*size)++] = c;
    (*ptr_arr)[*size] = '\0';
}

void copy_arr(char *dest, const char *src);
void increase_arr(char **ptr_arr, unsigned long new_size)
{
    char *tmp_arr = malloc(new_size);
    if(!tmp_arr) {
        perror("Error in memory allocation for array `increase_arr`");
        exit(4);
    }

    copy_arr(tmp_arr, *ptr_arr);
    free(*ptr_arr);
    *ptr_arr = tmp_arr;
}

void copy_arr(char *dest, const char *src)
{
    unsigned long i;
    for(i = 0; (dest[i] = src[i]); ++i) {
    }
}

void list_print_nodes(list *l)
{
    while(l) {
        if(l->vector[0] != '\0' && l->next) /* don't print extra space */
            printf("%s ", l->vector);
        else if(l->vector[0] != '\0')
            printf("%s", l->vector);
        
        l = l->next;
    }
    putchar('\n');
}

void list_free_memory(list **ptr_l)
{
    if(!*ptr_l)
        return;

    while(*ptr_l) {
        list *cur = *ptr_l;
        *ptr_l = (*ptr_l)->next;
        free(cur->vector);
        free(cur);
    } /* set NULL automatically */
}
