/* print words in vertical -- not horizontal */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE_OF_VECTOR  8
typedef struct tag_item {
    char *vector;
    unsigned long vector_max_size, vector_current_size;
    struct tag_item *next;
} item;

typedef struct tag_queue {
    item *first, *last;
} queue;

void queue_push_c(queue **ptr_que, char c);
void item_print_all(item *node);
void queue_free_memory(queue **ptr_que);
int main(void)
{
    queue *que = NULL;
    int c;

    while((c = getchar()) != EOF)
        if(c != '\n')
            queue_push_c(&que, c);
        else if(que){
            item_print_all(que->first);
            queue_free_memory(&que);
        }
    /* in case if last char != '\n' */
    if(que) {
        item_print_all(que->first);
        queue_free_memory(&que);
    }
    return 0;
}

void queue_init(queue **ptr_que);
void arr_push_c(char **ptr_arr, unsigned long *cur_size, unsigned long *limit,
                                                                       char c);
item *item_create_new(void);
void queue_push_c(queue **ptr_que, char c)
{
    if(c != ' ' && c != '\t' && c != '\n') {
        if(!*ptr_que)
            queue_init(ptr_que);

        arr_push_c(&(*ptr_que)->last->vector,
                   &(*ptr_que)->last->vector_current_size,
                   &(*ptr_que)->last->vector_max_size,
                   c);
    } else if(*ptr_que)
        if((*ptr_que)->last->vector[0] != '\0') {
            item *tmp_item = item_create_new();
            (*ptr_que)->last->next = tmp_item;
            (*ptr_que)->last = (*ptr_que)->last->next;
        }
}

item *item_create_new(void)
{
    item *new_item = malloc(sizeof(item));
    if(!new_item) {
        perror("Fail allocation for item in ```item_create_new```");
        exit(1);
    }

    new_item->vector = malloc(DEFAULT_SIZE_OF_VECTOR);
    if(!new_item->vector) {
        perror("Fail allocation for array in ```item_create_new```");
        exit(2);
    }

    new_item->vector[0] = '\0';
    new_item->vector_current_size = 0;
    new_item->vector_max_size = DEFAULT_SIZE_OF_VECTOR;
    new_item->next = NULL;
    return new_item;
}

void queue_init(queue **ptr_que)
{
    (*ptr_que) = malloc(sizeof(queue));
    if(!(*ptr_que)) {
        perror("Fail allocation for queue in ```queue_init```");
        exit(3);
    }

    (*ptr_que)->first = (*ptr_que)->last = item_create_new();
}

void copy_arr(char dest[], const char src[])
{
    unsigned long i;
    for(i = 0; (dest[i] = src[i]); ++i) {
    }
}

void arr_increase(char **ptr_arr, unsigned long new_size)
{
    char *tmp_arr = malloc(new_size);
    if(!tmp_arr) {
        perror("Fail allocation for temporary arr in ```arr_increase```");
        exit(4);
    }

    copy_arr(tmp_arr, *ptr_arr);
    free(*ptr_arr);
    *ptr_arr = tmp_arr;
}

void arr_push_c(char **ptr_arr, unsigned long *cur_size, unsigned long *limit,
                                                                      char c)
{
    if(*cur_size >= *limit - 1) {
        *limit *= 2;
        arr_increase(ptr_arr, *limit);
    }

    (*ptr_arr)[(*cur_size)++] = c;
    (*ptr_arr)[(*cur_size)] = '\0';
}

void item_print_all(item *node)
{
    unsigned long cur_poz = 0, max_size_poz = 0;
    item *runner = node;
    while(runner) {
        if(max_size_poz < runner->vector_current_size)
            max_size_poz = runner->vector_current_size;
        runner = runner->next;
    }

    while(max_size_poz) {
        for(runner = node; runner; runner = runner->next) {
            if(runner->vector_current_size != 0 &&
            cur_poz <= runner->vector_current_size - 1)
                putchar(runner->vector[cur_poz]);
            else 
                putchar(' ');
        }
        putchar('\n');

        ++cur_poz;
        --max_size_poz;
    }
}

void queue_free_memory(queue **ptr_que)
{
    item *tmp_item;
    if(!(*ptr_que))
        return;

    tmp_item = (*ptr_que)->first;
    while(tmp_item) {
        item *next = tmp_item->next;
        free(tmp_item->vector);
        free(tmp_item);
        tmp_item = next;
    }

    free(*ptr_que);
    *ptr_que = NULL;
}
