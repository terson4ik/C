/* print statistic about largest strings in specified files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORKING_SIZE_BUFF   4
typedef struct pseudo_vector {
    size_t  length, cur_size;
    char    *str;
} vector;

typedef struct tag_file_data_item {
    vector *largest_str;
    struct tag_file_data_item *next;
} file_data_item ;

vector *get_largest_str(const char *file_name);
vector *new_vector();
file_data_item *new_item(void);
void print_statistic(file_data_item *item, char **files_name); 
void free_list(file_data_item **item);
vector *new_vector();

int main(int argc, char **argv)
{
    file_data_item *first = NULL, *last = NULL;
    int num_file;

    if(argc < 2) {
        fprintf(stderr, "Example of use: \"./prog one.txt second.txt....\"\n");
        return 1;
    }

    for(num_file = 1; num_file < argc; ++num_file) {
        file_data_item *new_itm = new_item();
        if(!(new_itm->largest_str = get_largest_str(argv[num_file]))) {
            perror(argv[num_file]);
            return 6;
        }
        if(first) {
            last->next = new_itm;
            last = last->next;
        } else
            first = last = new_itm;
    }

    print_statistic(first, argv + 1);

    last = NULL;
    free_list(&first);
    
    return 0;
}

file_data_item *new_item(void)
{
    file_data_item *nw_i = malloc(sizeof(file_data_item));
    if(!nw_i) {
        perror("In function ``new_item``");
        exit(2);
    }

    nw_i->largest_str = NULL;
    nw_i->next = NULL;
    return nw_i;
}

vector *new_vector()
{
    vector *nw_v = malloc(sizeof(vector));
    if(!nw_v)
        return NULL;

    if(!(nw_v->str = malloc(WORKING_SIZE_BUFF)))
        return NULL;

    nw_v->length = WORKING_SIZE_BUFF;
    nw_v->cur_size = 0;
    return nw_v;
}

vector *get_largest_str(const char *file_name)
{
    FILE *src;
    vector *new_vec;
    char *buf;
    size_t len, len_of_buf, max;
    
    if(!(src = fopen(file_name, "r")))
        return NULL;
    if(!(new_vec = new_vector()))
        return NULL;
    if(!(buf = malloc(WORKING_SIZE_BUFF)))
        return NULL;
    len_of_buf = WORKING_SIZE_BUFF;
    max = len = 0;
    while(fgets(buf, len_of_buf, src)) {
        len = strlen(buf);
        while(buf[len - 1] != '\n') {
            len_of_buf *= 2;
            buf = realloc(buf, len_of_buf);
            if(!fgets(buf + len, len_of_buf - len, src))
                break;
            len += strlen(buf + len);
        }
        if(max < len) {
            max = len;
            if(len_of_buf > new_vec->length) {
                new_vec->length = len_of_buf;
                new_vec->str = realloc(new_vec->str, new_vec->length);
            }
            strncpy(new_vec->str, buf, len_of_buf);
            new_vec->cur_size = max;
        }
    }
    fclose(src);
    free(buf);

    return new_vec;
}

void print_statistic(file_data_item *item, char **files_name)
{
    file_data_item *tmp = item;
    size_t largest = 0;
    int i;

    while(tmp) {
        if(largest < tmp->largest_str->cur_size)
            largest = tmp->largest_str->cur_size;
        tmp = tmp->next;
    }
    
    i = 0;
    while(item) {
        if(item->largest_str->cur_size == largest)
            putchar('*');
        printf("%s:%s", files_name[i], item->largest_str->str);
        item = item->next;
        ++i;
    }
}

void free_list(file_data_item **item)
{
    while(*item) {
        file_data_item *cur = *item;
        *item = (*item)->next;
        free(cur->largest_str->str);
        free(cur->largest_str);
        free(cur);
    }
}
