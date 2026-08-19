/* 7.8) analog of pr in GNUs coreutils */
#include <stdio.h>

enum { PAGE_HIGH = 66, PAGE_WIDTH = 72 };

int main(int argc, char **argv)
{
    unsigned int pg_n;
    FILE *fsrc;
    if (argc < 2) {
        fputs("Bad usage, need name of the file\n", stderr);
        return 1;
    }
    pg_n = 0;
    while (*++argv) {
        unsigned int pg_line, pg_width;
        char *cur_name;
        int c;
        fsrc = fopen(cur_name = *argv, "r");
        if (!fsrc) {
            perror(*argv);
            return 2;
        }
        pg_n++;
        pg_width = 0;
        printf("\n%s\tPage %d\n", cur_name, pg_n);
        pg_line = 3;
        while ((c = fgetc(fsrc)) != EOF) {
            pg_width++;
            if (c == '\n' || pg_width > PAGE_WIDTH) {
                pg_width = 0;
                pg_line++;
                if (pg_line > PAGE_HIGH) {
                    pg_n++;
                    printf("\n%s\tPage %d\n", cur_name, pg_n);
                    pg_line = 3;
                } else 
                    putchar('\n');
            }
            putchar(c);
        }
        if (pg_line != 3)
            while (pg_line++ <= PAGE_HIGH)
                putchar('\n');
    }
    return 0;
}
