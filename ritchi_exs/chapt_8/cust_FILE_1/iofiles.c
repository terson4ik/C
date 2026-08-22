#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "iofiles.h"

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, 0, { 1 } },
    { 0, (char *) 0, (char *) 0, 1, { 0, 1 } },
    { 0, (char *) 0, (char *) 0, 2, { 0, 1, 1} },
};
#define PERMS 0666
FILE *fopen(const char *name, const char *mode)
{
    FILE *fp;
    int fd;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp  = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag.read == 0 && fp->flag.write == 0)
            break; /* find free place for file */
    if (fp >= _iob + OPEN_MAX) /* no free places */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flag.read = 1;
        fp->flag.write = 0;
    } else {
        fp->flag.read = 0;
        fp->flag.write = 1;
    }
    fp->flag.unbuf = fp->flag.eof = fp->flag.err = 0;

    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;
    if (!fp->flag.read || fp->flag.eof || fp->flag.err)
        return EOF;
    bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag.eof = 1;
        else
            fp->flag.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    return 0;
}
