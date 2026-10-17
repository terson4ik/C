#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
static int my_strcmp(const char *s1, const char *s2);

enum os_halts {
    OS_ARGS_ERROR   = 1,
    OS_FILE_ERROR   = 2,
    OS_UNKOWN_ERROR = 3
};
enum node_info {
    STR_MAX_SIZE   = 60, 
    INT_WID        = 4, 
    FIELD_MAX_SIZE = STR_MAX_SIZE + INT_WID
};

enum return_values { OK, FILE_ERR = -1 };

static enum return_values create_summary(int fd1, int fd2, int fd_rslt);
static int open_data_base(const char *fname);
static enum return_values read_one_field(char buf[FIELD_MAX_SIZE], int fd);
static void buf_fetch_count(char buf[FIELD_MAX_SIZE], unsigned int *count);
static void buf_write_count(char buf[FIELD_MAX_SIZE], unsigned int count);
static void my_memcpy(void *dst, const void *src, ssize_t size);

int main(int argc, char **argv)
{
    int fd1, fd2, fd_rslt;

    if (argc < 4) {
        fprintf(stderr, "Usage: summary FILE1 FILE2 RES\n");
        return OS_ARGS_ERROR;
    }

    fd1     = open_data_base(argv[1]);
    fd2     = open_data_base(argv[2]);
    fd_rslt = open(argv[3], O_WRONLY | O_CREAT | O_CLOEXEC, 0666);
    if (fd1 == FILE_ERR || fd2 == FILE_ERR || fd_rslt < 0)
        return OS_FILE_ERROR;


    switch (create_summary(fd1, fd2, fd_rslt)) {
    case OK:         return 0;
    case FILE_ERR: return OS_FILE_ERROR;
    default:         return OS_UNKOWN_ERROR;
    }
}

static enum return_values create_summary(int fd1, int fd2, int fd_reslt)
{
    char fir_buf[FIELD_MAX_SIZE];
    char sec_buf[FIELD_MAX_SIZE];
    unsigned int count;

    return OK;
}


static enum return_values read_one_field(char buf[FIELD_MAX_SIZE], int fd)
{
    int count = read(fd, buf, FIELD_MAX_SIZE);
    if ((count != FIELD_MAX_SIZE && count != 0) || count < 0)
        return FILE_ERR;
    return (count == FIELD_MAX_SIZE) ? 1 : 0;
}

static int open_data_base(const char *fname)
{
    off_t size;
    int fd = open(fname, O_RDONLY);
    if (fd < 0)
        return FILE_ERR;

    size = lseek(fd, 0, SEEK_END);
    if (size == 0 || size % FIELD_MAX_SIZE != 0) {
        fprintf(stderr, (size == 0) ? 
                        "%s: file empty\n" :
                        "%s: unknown data format\n",
                        fname);
        close(fd);
        return FILE_ERR;
    }

    lseek(fd, 0, SEEK_SET);
    return fd;
}

static void buf_fetch_count(char buf[FIELD_MAX_SIZE], unsigned int *count)
{
    my_memcpy(count, buf+STR_MAX_SIZE, INT_WID);
}

static void buf_write_count(char buf[FIELD_MAX_SIZE], unsigned int count)
{
    my_memcpy(buf+STR_MAX_SIZE, &count, INT_WID);
}

static void my_memcpy(void *dst, const void *src, ssize_t size)
{
    char *d = dst;
    char *s = src;

    while (size-- > 0)
        *d++ = *s;
}

static int my_strcmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 1;
    return 0;
}
