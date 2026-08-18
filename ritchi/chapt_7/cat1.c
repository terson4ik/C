#include <stdio.h>

#if 0
#define getchar() getc(stdin)
#define putchar(c) putc((c), stdout)
#endif

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char **argv)
{
    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0) {
            FILE *fp = fopen(*++argv, "r");
            if (!fp) {
                printf("cat: can't open %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    return 0;

}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
} 
