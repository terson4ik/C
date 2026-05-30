#include <stdio.h>
#include <stdlib.h>

int str_len(const char *str)
{
    const char *temp = str;
    for(; *temp; temp++)
    {}
    return temp - str;
}

char *new_char_arr(int size)
{
    return (char*)malloc(size);
}
char *copy_arr(char *dest, const char *src)
{
    int i;
    for(i = 0; src[i]; i++)
        dest[i] = src[i];
    dest[i] = 0;
    return dest;
}

char *big_letters(char *arr)
{
    int i;
    for(i = 0; *(arr + i); i++) {
        if(arr[i] >= 'a' && arr[i] <= 'z') {
            /*
             a =  0110 0001
             A =  0100 0001
            */
            arr[i] &= 0b11011111;
        }
    }
    return arr;
}

char **create_pseudo_argv(const int argc, const char **argv)
{
    char **res;
    int i, j;
    res = (char**)malloc(sizeof(char**) * argc);
    res[argc - 1] = NULL;
    /*           - 2 because 1 as index, 1 as ./prog */
    for(i = argc - 2, j = 1; i >= 0; i--, j++)
        res[i] = copy_arr(new_char_arr(1 + str_len(argv[j])), argv[j]);
    return res;
}

void clean_argv(char **argv)
{
    int i;
    for(i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
}

int main(int argc, char **argv)
{
    int i;
    char **argvvv = create_pseudo_argv(argc, (const char **)argv);
    for(i = 0; argvvv[i]; i++) 
        printf("%s\n", big_letters(argvvv[i]));
    clean_argv(argvvv);
    return 0;
}
