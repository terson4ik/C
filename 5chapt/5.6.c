#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
static int str_is_num(const char *s);
static unsigned int myatoui(const char *s);
static void shufle(char *in_place_bufer, int count, unsigned int key);

static const char no_count_msg[] = "Usage: xor FILE KEY(32bits/4bytes)\n";
int main(int argc, char **argv)
{
    enum { BUF_SIZE = 4096 };
    unsigned int key;
    int frwd, count;
    char buf[BUF_SIZE], *file_name, *argv_key;
    if (argc < 3) {
        write(STDERR_FILENO, no_count_msg, sizeof(no_count_msg)-1);
        return 1;
    }
    file_name = argv[1];
    argv_key  = argv[2];

    if (!str_is_num(argv_key)) {
        fprintf(stderr, "%s: not a number(minus non supported)\n", argv_key);
        return 2;
    }

    frwd = open(file_name, O_RDWR);
    if (frwd < 0) {
        perror(file_name);
        return 3;
    }

    key = myatoui(argv_key);
    
    while ((count = read(frwd, buf, BUF_SIZE)) > 0) {
        shufle(buf, count, key);
        lseek64(frwd, -count, SEEK_CUR);
        write(frwd, buf, count);
    }
    if (count < 0) {
        perror(file_name);
        return 4;
    }

    close(frwd);
    return 0;
}

static int str_is_num(const char *s)
{
    for ( ; *s; s++)
        if (*s>'9' || *s<'0')
            return 0;
    return 1;
}

static unsigned int myatoui(const char *s)
{
    unsigned int res;
    for (res = 0; *s; s++)
        res = res*10 + *s-'0';
    return res;
}

static void shufle(char *in_place_bufer, int count, unsigned int key)
{
    int *int_ptr = (int *)in_place_bufer;
    for ( ; count >= 4; count -= 4, int_ptr++)
        *int_ptr ^= key;

    if (count > 0) {
        char *byte_ptr = (char *)int_ptr;
        char *bytes_of_key = (char *)&key;
        for( ; count > 0; count--)
            *(byte_ptr++) ^= *(bytes_of_key++);
    }
}
