#ifndef MY_IOFILES_H
#define MY_IOFILES_H

#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max count opened files */
#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])
#define feof(p)     (((p)->flag.eof ) != 0)
#define ferror(p)   (((p)->flag.err) != 0)
#define fileno(p)   ((p)->fd)

typedef struct _iobuf {
    int cnt;    /* how much is left chars */
    char *ptr;  /* next char position */
    char *base; /* place of buffer */
    int fd;     /* file descriptor */
    struct {
        unsigned int read : 1;
        unsigned int write : 1;
        unsigned int unbuf : 1;
        unsigned int eof : 1;
        unsigned int err : 1;
    } flag;
} FILE;

extern FILE _iob[OPEN_MAX];


#define getc(p)     (--(p)->cnt >= 0 \
                ? (unsigned char) *p->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)
int _fillbuf(FILE *inp);
int _flushbuf(int c, FILE *out);
int fseek(FILE *fp, long ofset, int origin);

FILE *fopen(const char *name, const char *mode);
int fflush(FILE *stream);
int fclose(FILE *stream);

#endif
