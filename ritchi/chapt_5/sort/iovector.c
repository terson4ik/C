#include <stdio.h>
#include "iovector.h"
#include "mstring.h"
#include "get_line.h"
#include "alloc.h"

#define MAXLEN 1000
int readlines(char *lineptr[], int maxlines)
{
    char line[MAXLEN];
    char *p;
    int len;
    int nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        p = alloc(len);
        if (nlines >= maxlines || p == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            my_strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
/* int i;
    for (i = 0; i < nlines; i++) */
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
static void swap(char *v[], int i, int j)
{
    char *tmp_adr = v[i];
    v[i] = v[j];
    v[j] = tmp_adr;
}

void qsort(char *v[], int left, int right)
{
    int last, i;
    if (left >= right)
        return;

    swap (v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (my_strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}
