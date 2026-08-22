#include <stdio.h>
#include <unistd.h>

/* lseek(fd, 0L, 2) -- set to end of file 
 * lseek(fd, 0l, 0) -- set to begin of file
 * --------------1- -- cur position */
int get(int fd, long pos, char *buf, int n);

int main()
{
    char buf[BUFSIZ];
    int n;
    n = get(0, 9, buf, 10);
    if (n >= 0) {
        write(1, buf, n);  
        return 0;
    } else
        return 1;
}

int get(int fd, long pos, char *buf, int n)
{
    if (lseek(fd, pos, 0) >= 0)
        return read(fd, buf, n);
    else
        return -1;
}
