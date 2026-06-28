/* print length statistic for specifics files */
#include <stdio.h>
#include <stdlib.h>

/* count of argv know, then use dynamic array */
typedef struct tag_meta_item {
    size_t  cur_len, edge;
    char    *str;
} meta_item;

void meta_item_arr_init(meta_item ***mega_ptr, int size);
int get_largest_line(meta_item *item, char *file_name);
void print_meta_data(meta_item **meta_arr, char **files_n, int size);
void meta_item_arr_del(meta_item ***mega_ptr, int size);
size_t find_max(meta_item **meta_arr, size_t size);
size_t str_size(const char *src);
void copy_str(char *dest, const char *src);
char *re_alloc(char *ptr, int new_size);

#define SIZE_FOR_ALLOCATE_ARR   256
int main(int argc, char **argv)
{
    meta_item **meta_arr = NULL;
    int i;

    if(argc < 2) {
        fprintf(stderr, "No file to read\n");
        return 1;
    }
                               /* without ./prog */
    meta_item_arr_init(&meta_arr, argc - 1);
    for(i = 1; i < argc; ++i) {
        if(!get_largest_line(meta_arr[i - 1], argv[i])) {
            perror(argv[i]);
            return 2;
        }
    }
    print_meta_data(meta_arr, argv + 1, argc - 1);

    meta_item_arr_del(&meta_arr, argc - 1);
    return 0;
}

void meta_item_arr_init(meta_item ***mega_ptr, int size)
{
    int i;
    if(!(*mega_ptr = malloc(sizeof(meta_item *) * size))) {
        perror("Meta arr init");
        exit(3);
    }

    for(i = 0; i < size; ++i) {
        if(!((*mega_ptr)[i] = malloc(sizeof(meta_item)))) {
            perror("Meta arr[i] init");
            exit(4);
        }
        (*mega_ptr)[i]->cur_len = 0;
        (*mega_ptr)[i]->edge = SIZE_FOR_ALLOCATE_ARR;
        if(!((*mega_ptr)[i]->str = malloc(SIZE_FOR_ALLOCATE_ARR))) {
            perror("Meta arr[i]->str init");
            exit(5);
        }
        (*mega_ptr)[i]->str[0] = '\0';
    }
}
int get_largest_line(meta_item *item, char *file_name)
{
    FILE *src;
    char *buf;
    size_t cur_len, buf_cur_len = SIZE_FOR_ALLOCATE_ARR; 
    if(!(buf = malloc(SIZE_FOR_ALLOCATE_ARR)))
        return 0;
    if(!(src = fopen(file_name, "r")))
        return 0;
    while(fgets(buf, buf_cur_len, src)) {
        cur_len = str_size(buf);
        while(buf[cur_len - 1] != '\n') {
            buf_cur_len *= 2;
            if(!(buf = re_alloc(buf, buf_cur_len))) {
                fclose(src);
                return 0;
            }
            if(!fgets(buf + cur_len, buf_cur_len - cur_len, src))
                break;
            cur_len += str_size(buf + cur_len);
        }
        if(cur_len > item->cur_len) {
            if(buf_cur_len > item->edge) {
                item->edge = buf_cur_len;
                if(!(item->str = re_alloc(item->str, item->edge))) {
                    free(buf);
                    fclose(src);
                    return 0;
                }
            }
            copy_str(item->str, buf);
            item->cur_len = cur_len;
        }
    }

    free(buf);
    fclose(src);
    return 1;
}
size_t str_size(const char *src)
{
    const char *tmp = src;
    for(; *tmp; ++tmp) {
    }
    return tmp - src;
}

void copy_str(char *dest, const char *src)
{
    char *t_d = dest;
    const char *t_s = src;
    for(; (*t_d = *t_s); ++t_d, ++t_s) {
    }
}

char *re_alloc(char *ptr, int new_size)
{
    char *new_arr;
    if(!(new_arr = malloc(new_size)))
        return NULL;

    copy_str(new_arr, ptr);
    free(ptr);
    return new_arr;
}

void print_meta_data(meta_item **meta_arr, char **files_n, int size)
{
    int i;
    size_t max;
    max = find_max(meta_arr, size);
    for(i = 0; i < size; ++i) {
        if(meta_arr[i]->cur_len == max)
            putchar('*');

        printf("%s:%s", files_n[i], meta_arr[i]->str);
    }
}

size_t find_max(meta_item **meta_arr, size_t size)
{
    int i; 
    size_t max = 0;
    for(i = 0; i < size; ++i)
        if(meta_arr[i]->cur_len > max)
            max = meta_arr[i]->cur_len;

    return max;
}

void meta_item_arr_del(meta_item ***mega_ptr, int size)
{
    int i;
    for(i = 0; i < size; ++i) {
        if((*mega_ptr)[i]->str)
            free((*mega_ptr)[i]->str);

        free((*mega_ptr)[i]);
    }

    free(*mega_ptr);
}
