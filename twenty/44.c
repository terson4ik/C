#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE_OF_VECTOR  9
typedef struct tag_item {
    unsigned long vector_current_size, vector_max_size;
    char *vector;
    struct tag_item *next;
} item;

typedef struct tag_queue {
    item *first, *last;
} queue;
/* public API */
void q_push_digit(queue **p_que, char c);
void q_print_all(item *node);
void q_free_memory(queue **p_que);
/* ```private``` functions */
queue *q_create_new();
item *i_create_new();
void arr_increase(char **p_arr, unsigned long new_size);
void arr_copy(char *dest, const char *src);
void arr_push(char **p_arr, unsigned long *cur_size, unsigned long *max_size,
                                                                    char c);
int main(void)
{
    queue *que = NULL;
    int c;
    while((c = getchar()) != EOF)
        if(c != '\n')
            q_push_digit(&que, c);
        else if(que) {
            q_print_all(que->first);
            q_free_memory(&que);
        }

    if(que) {
        q_print_all(que->first);
        q_free_memory(&que);
    }
    return 0;
}


void q_push_digit(queue **p_que, char c)
{
    if(c >= '0' && c <= '9') {
        if(!*p_que)
            *p_que = q_create_new();

        arr_push(&(*p_que)->last->vector,
                 &(*p_que)->last->vector_current_size,
                 &(*p_que)->last->vector_max_size, c);
    } else if(*p_que)
        if((*p_que)->last->vector[0] != '\0') {
            item *new_item = i_create_new();
            (*p_que)->last->next = new_item;
            (*p_que)->last = (*p_que)->last->next;
        }
}

void q_print_all(item *node)
{
    item *tmp = node;
    unsigned long max_length = 0;
    while(tmp) {
        if(max_length < tmp->vector_current_size)
            max_length = tmp->vector_current_size;
        tmp = tmp->next;
    }

    while(node) {
        if(node->vector_current_size == max_length) {
            if(node->next)
                printf("%s ", node->vector);
            else
                printf("%s", node->vector);
        }
        node = node->next;
    }
    putchar('\n');
}

void q_free_memory(queue **p_que)
{
    if(!*p_que)
        return;

    while((*p_que)->first) {
        item *cur_node = (*p_que)->first;
        (*p_que)->first = (*p_que)->first->next;
        free(cur_node->vector);
        free(cur_node);
    }

    free(*p_que);
    *p_que = NULL;
}

item *i_create_new()
{
    item *new_item = malloc(sizeof(item));
    if(!new_item) {
        perror("Fatal Error in allocation for new item in ```i_create_new```");
        exit(1);
    }

    new_item->vector = malloc(DEFAULT_SIZE_OF_VECTOR);
    if(!new_item->vector) {
        perror("Fatal Error in allocation for new arr in ```i_create_new```");
        exit(2);
    }

    new_item->vector_max_size = DEFAULT_SIZE_OF_VECTOR;
    new_item->vector_current_size = 0;
    new_item->vector[0] = '\0';
    new_item->next = NULL;
    return new_item;
}

queue *q_create_new()
{
    queue *new_q = malloc(sizeof(queue));
    if(!new_q) {
        perror("Fatal Error in allocation for new queue in ```q_create_new```");
        exit(3);
    }
    new_q->first = new_q->last = i_create_new();
    return new_q;
}

void arr_push(char **p_arr, unsigned long *cur_size, unsigned long *max_size,
                                                                    char c)
{
    if(*cur_size >= *max_size) {
        *max_size *= 2;
        arr_increase(p_arr, *max_size);
    }

    (*p_arr)[(*cur_size)++] = c;
    (*p_arr)[(*cur_size)] = '\0';
}

void arr_increase(char **p_arr, unsigned long new_size)
{
    char *new_arr = malloc(new_size);
    arr_copy(new_arr, *p_arr);
    free(*p_arr);
    *p_arr = new_arr;
}

void arr_copy(char *dest, const char *src)
{
    unsigned long i;
    for(i = 0; (dest[i] = src[i]); ++i) {
    }
}
