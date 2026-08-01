#include <stdio.h>
#include "gline_strings.h"

#define MAXLINE 1000
int main (int argc, char *argv[])
{
    char line[MAXLINE];
    int find = 0;

    if (argc != 2)
        fprintf(stderr, "Usage: find pattern\n");
    else
        while (get_line(line, MAXLINE) > 0)
            if (str_str(line, argv[1])) {
                printf("%s", line);
                find++;
            }
    return find;
}
