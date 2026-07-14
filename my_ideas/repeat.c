#include <stdio.h>
#include <stdlib.h>

#define HELP_MSG "Example of use: \"./prog 20 word\" or" \
                 "\"./prog -n 20 word\" for turn on new line mode.\n"

#define ERR_MSG "Count is negative.\n"

#define IS_NUM(x) ((x) >= '0' && (x) <= '9')
size_t a_to_sizeT(const char *num_str);

int main(int argc, char **argv)
{
    size_t i;
    char space, *start_word;
    if(argc < 3) {
        fprintf(stderr, HELP_MSG);
        return 1;
    }
    if(argc == 3) {
        space = ' ';
        start_word = argv[2];
        i = a_to_sizeT(argv[1]);
    } else {
        if(argv[1][0] != '-' && argv[1][1] != 'n') {
            fprintf(stderr, "Invalid flag. -n for new lines");
            return 4;
        }
        space = '\n';
        start_word = argv[3];
        i = a_to_sizeT(argv[2]);
    }
    for(; i; --i) {
        printf("%s%c", start_word, space);
    }
    putchar('\n');

    return 0;
}

size_t a_to_sizeT(const char *num_str)
{
    int i;
    size_t res = 0;
    for(i = 0; num_str[i]; ++i) {
        if(!IS_NUM(num_str[i])) {
            fprintf(stderr, "It's not a number.\n");
            exit(3);
        }
        res = res * 10 + num_str[i] - '0';
    }
    return res;
}
