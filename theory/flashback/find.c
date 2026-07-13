#include <stdio.h>

int match(const char *str, const char *pat);
int main(int argc, char **argv)
{
    if(argc < 3) {
        fprintf(stderr, "Example of use: ./prog string pattern\n");
        return 1;
    }

    if(match(argv[1], argv[2]))
        puts("YES");
    else
        puts("NO");

    return 0;
}

int match(const char *str, const char *pat)
{
    int i;
    for(;; ++str, ++pat) {
        switch(*pat) {
            case '?':
                if(!*pat)
                    return 0;
                continue;
            break;
            case '*':
                for(i = 0; ; ++i) {
                    if(match(str + i, pat + 1))
                        return 1;
                    if(!str[i])
                        return 0;
                }
            break;
            case '\0':
                return *str == '\0';
            break;
            default:
                if(*pat != *str)
                    return 0;
        }
    }
    return 1;
}
