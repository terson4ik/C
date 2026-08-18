#include <stdio.h>

char *my_fgets(char *str, int lim, FILE *inpf);
int my_fputs(const char *str, FILE *outf);
int my_getline(char *str, int lim);

#define MAXLINE 299
int main()
{
    char line[MAXLINE];
    my_fgets(line, MAXLINE, stdin);
    my_fputs(line, stdout);
    printf("%d\n", my_getline(line, MAXLINE));
    my_fputs(line, stdout);
    return 0;
}

char *my_fgets(char *str, int lim, FILE *inpf)
{
    int c;
    char *r = str;
    while (--lim > 0 && (c = getc(inpf)) != EOF)
        if ((*r++ = c) == '\n')
            break;
    *r = '\0';
    return (c == EOF && r == str) ? NULL : str;
}

int my_fputs(const char *str, FILE *outf)
{
    while (*str)
        putc(*str++, outf);
    return ferror(outf) ? EOF : 0;
}

int str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r - s;
}

int my_getline(char *str, int lim)
{
    if (my_fgets(str, lim, stdin) == NULL)
        return 0;
    else
        return str_len(str);
}
