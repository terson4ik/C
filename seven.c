#include <stdio.h>
#include <stdlib.h>

int str_size(const char *str) 
{
    int i;
    for(i = 0; str[i]; i++)
    {}
    return i;
}

char *str_copy(char *dest, const char *src)
{
    char *t_dest = dest;
    const char *t_src = src;
    for(; *t_src; t_src++, t_dest++)
        *t_dest = *t_src;
    return dest;
}

char *remove_spices(char *str)
{
    int i;
    char *temp_arr = (char*)malloc(str_size(str) + 1);
    char *t = temp_arr;
    str_copy(temp_arr, str);
    for(i = 0; *temp_arr; temp_arr++) {
        if(*temp_arr != ' ') {
            *(str + i) = *temp_arr;
            ++i;
        }
    }
    *(str + i) = 0;
    free(t);
    return str;
}

int count_spaces(const char *str)
{
    int i, j;
    for(j = i = 0; str[i]; i++) {
        if(*(str + i) == ' ')
            ++j;
    }
    return j;
}

int main(int argc, char **argv)
{
    char *str;
    if(argc != 2) {
        fprintf(stderr, "Need one word \" word \"\n");
        return 1;
    }
    str = (char*)malloc(str_size(*(argv + 1)) + 1);
    /* sizeof is full shit
     * newer use this deep shit
     */
    str_copy(str, argv[1]);
    printf("before removing:      %s\n", str);
    printf("after removing:       %s\n", remove_spices(str));
    printf("spices BEFORE remove: %d\n", count_spaces(argv[1]));
    printf("and AFTER remove:     %d\n", count_spaces(str));
    return 0;
}
