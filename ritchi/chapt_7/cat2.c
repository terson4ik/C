#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char **argv)
{
    char *name = argv[0];
    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while(--argc > 0) {
            FILE *fp = fopen(*++argv, "r");
            if (!fp) {
                fprintf(stderr, "%s: can't open %s", name, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", name);
        exit(2);
    }
    exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
