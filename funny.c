#include <stdio.h>

int size_str(const char *str);
int find_max(char **p_str);
void print_vertical_args(char **argv, int max_len);
int main(int argc, char **argv)
{
    if(argc < 2)
        return 0;
    print_vertical_args(argv, find_max(argv));
    return 0;
}

int size_str(const char *str)
{
    const char *tmp;
    for(tmp = str; *tmp; ++tmp){
    }
    return tmp - str;
}

int find_max(char **p_str)
{
    int max, i;
    for(max = 0, i = 1; p_str[i]; ++i) {
        int size = size_str(p_str[i]);
        if(max < size)
            max = size;
    }
    return max;
}

void print_vertical_args(char **argv, int max_len)
{
    int cur;
    for(cur = 0; max_len > cur; ++cur) {
        int i;
        for(i = 1; argv[i]; ++i) {
            int size = size_str(argv[i]);
            if(cur < size)
                putchar((argv[i])[cur]);
            else
                putchar(' ');
        }
        putchar('\n');
    }
}
