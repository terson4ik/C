#include <stdio.h>

void print_without_minus(const char *str)
{
    if(*str == '-' || *str == 0)
        return;
    printf("%s\n", str);
}

int main(int argc, char **argv)
{
    int i;
    if(!(argc - 1)) {
        fprintf(stderr, "I need the arguments!!!\n");
        return 1;
    }
    for(i = 1; i < argc; i++) {
        print_without_minus(*(argv + i));
    }
    return 0;
}
