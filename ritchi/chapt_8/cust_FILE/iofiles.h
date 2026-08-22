#ifndef MY_IOFILES_H
#define MY_IOFILES_H

#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max count opened files */
#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])
#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

typedef struct _iobuf {
    int cnt;    /* how much is left chars */
    char *ptr;  /* next char position */
    char *base; /* place of buffer */
    int flag;   /* mode of permission the file */
    int fd;     /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

enum _flags {
    _READ   = 01,   /* file open for read */
    _WRITE  = 02,   /* --------------write */
    _UNBUF  = 04,   /* file without buffering */
    _EOF    = 010,  /* fine end of file */
    _ERR    = 020   /* an error occurred */
};

#define getc(p)     (--(p)->cnt >= 0 \
                ? (unsigned char) *p->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE *fopen(const char *name, const char *mode);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#endif
