#include <stdio.h>
#include "gline_strings.h"

#define MAXLINE 1000
int main (int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, number = 0, except = 0, find = 0;

    while(--argc > 0 && (*++argv)[0] == '-') 
        while((c = *(++argv[0])))
            switch(c) {
                case 'n':
                    number = 1;
                    break;
                case 'x':
                    except = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    find = -1;
                    break;
            }
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while (get_line(line, MAXLINE) > 0) {
            lineno++;
            if ((str_str(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                find++;
            }
        }
    return find;
}
