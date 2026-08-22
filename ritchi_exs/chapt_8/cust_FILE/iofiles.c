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
int fflush(FILE *stream)
{
    return _flushbuf(EOF, stream);
}

int fclose(FILE *stream)
{
    if (stream->base) {
        if (stream->flag.write)
            fflush(stream);
        free(stream->base);
    }
    stream->ptr = stream->base = NULL;
    stream->flag.read = stream->flag.write = stream->flag.eof = 
                            stream->flag.err = stream->cnt = 0;
    return close(stream->fd);
}

int fseek(FILE *fp, long ofset, int origin)
{
    /* buffer will broken, then reset it */
    if (fp->flag.write)
        fflush(fp);
    if (origin == 1 && fp->flag.read)
        ofset -= fp->cnt;
    fp->ptr = fp->base;
    fp->cnt = fp->flag.eof = 0;
    return lseek(fp->fd, ofset, origin) < 0 ? 1 : 0;
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

int _flushbuf(int c, FILE *out)
{
    int n, cnt;
    if (out->flag.read || out->flag.err)
        return EOF;
    if (out->base == NULL && !out->flag.unbuf && c != EOF) {
        out->ptr = out->base = malloc(out->cnt = BUFSIZ);
        if (!out->base)
            return -1;
        *out->ptr++ = c;
        out->cnt--;
        return 0;
    }
    if (out->flag.unbuf) {
        if (write(out->fd, &c, 1) != 1)
            return -1;
        else
            return 0;
    }
    if (out->base == NULL)
        return EOF;
    cnt = out->ptr - out->base;
    if ((n = write(out->fd, out->base, cnt)) != cnt)
        return -1;
    out->ptr = out->base;
    out->cnt = BUFSIZ;
    if (c != EOF) {
        *out->ptr++ = c;
        out->cnt--;
    }
    return n;
}
