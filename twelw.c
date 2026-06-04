#include <stdio.h>

#define TOTAL_COMPLETE

#ifndef TOTAL_COMPLETE
int str_len(const char *str)
{
    const char *tmp;
    for(tmp = str; *tmp; ++tmp)
    {}
    return tmp - str;
}
#endif

const char* find_substr(const char *orig, const char *substr)
{
    int i, j;

    for(i = 0; orig[i]; ++i) {
        for(j = 0; substr[j]; ++j)
            if(substr[j] != orig[i + j])
                break; /* if brake then sub_str don't end */

        if(!substr[j]) /* if end of string then */
            return orig + i;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int i, count;
#ifndef TOTAL_COMPLETE
    int size_pattern;
#endif
    const char *temp_adr;
    if(argc < 2)
        return 1;
    else if(argc == 2)
        return 0;

    printf("a)\n");
    for(i = 2; i < argc; ++i)
        if(find_substr(argv[i], argv[1]))
            printf("%s\n", argv[i]);

    printf("b)\n");
#ifndef TOTAL_COMPLETE
    size_pattern = str_len(argv[1]);
#endif
    for(i = 2; i < argc; ++i)
        if((temp_adr = find_substr(argv[i], argv[1]))) {
#ifndef TOTAL_COMPLETE
            temp_adr += size_pattern;
#else
            ++temp_adr;
#endif
            for(count = 1; (temp_adr = find_substr(temp_adr, argv[1])); ++count)
#ifndef TOTAL_COMPLETE
                temp_adr += size_pattern;
#else
                ++temp_adr;
#endif
            printf("%s | %d\n", argv[i], count);
        }

    return 0;
}
