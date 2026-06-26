/* print statistic about largest strings in specified files */
#include <stdio.h>
#include <stdlib.h>

#define WORKING_SIZE_BUFF   16384
typedef struct pseudo_vector {
    size_t  length;
    char    *str;
} vector;

typedef struct tag_file_data_item {
    vector *largest_str;
    struct tag_file_data_item *next;
} file_data_item ;

vector *get_largest_str(const char *file_name);
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

vector *get_largest_str(const char *file_name)
{
    FILE *src;
    vector *new_vec;
    size_t anchor, length, max_len, read_bytes, max_pos;
    char *buf;
    
    if(!(src = fopen(file_name, "r")))
       return NULL;
    if(!(buf = malloc(WORKING_SIZE_BUFF)))
        return NULL;

    anchor = length = max_len = 0;
    while((read_bytes = fread(buf, 1, WORKING_SIZE_BUFF, src))) {
        size_t tmp;
        for(tmp = 0; tmp < read_bytes; ++tmp, ++anchor) {
            if(buf[tmp] != '\n')
                ++length;
            else {
                if(max_len < length){
                    max_len = length;
                    max_pos = anchor - length;
                }
                length = 0;
            }
        }
    }
    free(buf);
    if(!feof(src) || ferror(src))
        return NULL;
    if(!(new_vec = malloc(sizeof(vector))))
        return NULL;

    if(length != 0) {
        if(max_len < length){
            max_len = length;
            max_pos = anchor - length;
        }
    }

    new_vec->length = max_len;
    if(!(new_vec->str = malloc(new_vec->length + 1)))
        return NULL;
    if(max_len) {
        fseek(src, max_pos, SEEK_SET);
        
        if(ferror(src))
            return NULL;
        if(!fgets(new_vec->str, max_len + 1, src))
            return NULL;
    } else
        new_vec->str[0] = '\0';

    return new_vec;
}

void print_statistic(file_data_item *item, char **files_name)
{
    file_data_item *tmp = item;
    size_t largest = 0;
    int i;

    while(tmp) {
        if(largest < tmp->largest_str->length)
            largest = tmp->largest_str->length;
        tmp = tmp->next;
    }
    
    i = 0;
    while(item) {
        if(item->largest_str->length == largest)
            putchar('*');
        printf("%s:%s\n", files_name[i], item->largest_str->str);
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
