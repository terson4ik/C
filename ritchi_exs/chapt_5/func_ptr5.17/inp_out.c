#include <stdio.h>
#include "inp_out.h"
#include "alloc.h"
#include "my_string.h"

static int get_line(char *s, int lim);

#define MAXLINE 500

int readlines(char *lineptr[], int limit)
{
    char line[MAXLINE];
    char **run_line_ptr = lineptr;
    int len;

    while ((len = get_line(line, MAXLINE)) > 0)
        if (limit-- > 0) {
            if (line[len-1] == '\n')
                line[len-1] = '\0';
            *run_line_ptr = alloc(len);
            if (!*run_line_ptr)
                return -1;
            my_str_cpy(*run_line_ptr++, line);
        } else
            return -1;

    return run_line_ptr - lineptr;
}

void writelines(char *lineptr[], int n)
{
    while (n-- > 0)
        printf("%s\n", *lineptr++); /* In readlines \n will removes */
}

static int get_line(char *s, int lim)
{
    int c;    
    char *run = s;
    while (--lim > 0 && (c = getchar()) != EOF) {
        *run++ = c;
        if (c == '\n')
            break;
    }
    *run = '\0';
    return run - s; 
}