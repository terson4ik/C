#include <stdio.h>
#include <unistd.h>

#define BUF 1

int get_c(void);
void put_c(int c);
void flush_c(void);

int main()
{
    int c;
    while ((c = get_c()) != EOF)
        put_c(c);
    flush_c();
    return 0;
}

#if BUF
int get_c(void)
{
    static char buf[BUFSIZ];
    static char *pbuf;
    static int n = 0;

    if (n == 0) {
        n = read(0, buf, sizeof buf);
        pbuf = buf;
    }
    return (--n >= 0) ? *pbuf++ : EOF;
}

static char pr_buf[BUFSIZ];
static char *pr_ptr = pr_buf;

void put_c(int c)
{
    if (pr_ptr < pr_buf + BUFSIZ)
        *pr_ptr++ = c;
    else
        flush_c();   
}

void flush_c(void)
{
    write(1, pr_buf, pr_ptr - pr_buf);
    pr_ptr = pr_buf;
}
#else 
int get_c(void)
{
    char c;

    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

void put_c(int c)
{
    char chr = c;
    write(1, &chr, 1);
}

void flush_c(void)
{
    write(1, "its non buffer\n", 15);
}
#endif
