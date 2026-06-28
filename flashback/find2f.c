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

int star_match(const char *str, const char *pat);
int match(const char *str, const char *pat)
{
    switch(*pat) {
        case '\0':
            return *str == '\0';
        break;
        case '?':
            return match(++str, ++pat);
        break;
        case '*':
            return star_match(str, pat + 1);
        break;
        default:
            if(*pat == *str)
                return match(++str, ++pat);
            else
                return 0;
    }
}

int star_match(const char *str, const char *pat)
{
    int i;
    for(i = 0; ; ++i) {
        if(match(str + i, pat))
            return 1;
        else if(!str[i])
            return 0;
    }
}
