#include <stdio.h>

int str_cmp(const char *s1, const char *s2);
int formating_cmp(const char *s1, const char *s2);

#define MAXLINE 2048
int main(int argc, char **argv)
{
    char ln1[MAXLINE], ln2[MAXLINE];
    FILE *f1, *f2;
    char eofs;
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

    eofs = 0;
    while (!eofs) {
        if (fgets(ln1, MAXLINE, f1) == NULL) {
            *ln1 = '\0';
            eofs = 1;
        }
        if (fgets(ln2, MAXLINE, f2) == NULL) {
            *ln2 = '\0';
            eofs = 2;
        }
        if (formating_cmp(ln1, ln2) != 0)
            break;
    }
    fclose(f1);
    fclose(f2);
    return 0;
}

int formating_cmp(const char *ln1, const char *ln2)
{
    int cond = str_cmp(ln1, ln2);
    if (cond == 0)
        return 0;
    printf("%c %s", ((cond > 0) ? '>' : '<'), ln1);
    fputs("---\n", stdout);
    printf("%c %s", ((cond > 0) ? '<' : '>'), ln2);
    return cond;
}

int str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && (*s1 == *s2))
        s1++, s2++;
    return (unsigned char)*s1 - (unsigned char)*s2;
}
