#include <stdio.h>

int str_cmp(const char *s1, const char *s2);

#define MAXLINE 2048
#define ONCE    0
int main(int argc, char **argv)
{
    char ln1[MAXLINE], ln2[MAXLINE];
    unsigned int nl;
    FILE *f1, *f2;
    if (argc < 3) {/* prog + 2 files */
        fputs("Example of use: prog f1.txt f2.txt\n", stderr);
        return 1;
    }
    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        perror(argv[1]);
        return 2;
    }
    f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
        fclose(f1);
        perror(argv[2]);
        return 2;
    }

    nl = 0;
    while (1) {
        nl++;
        char *t1 = fgets(ln1, MAXLINE, f1);
        char *t2 = fgets(ln2, MAXLINE, f2);
        if (t1 == NULL && t2 == NULL)
            break;
        else if (t1 == NULL)
            *ln1 = '\0';
        else if (t2 == NULL)
            *ln2 = '\0';
        if (str_cmp(ln1, ln2) != 0) {
            fprintf(stderr, "%d\n", nl);
            printf("< %s---\n> %s", ln1, ln2);
#if ONCE
            break;
#endif
        }

    }
    fclose(f1);
    fclose(f2);
    return 0;
}

int str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && (*s1 == *s2))
        s1++, s2++;
    return (unsigned char)*s1 - (unsigned char)*s2;
}
