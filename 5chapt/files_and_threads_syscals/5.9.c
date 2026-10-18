#include <stdio.h>
#include <sys/stat.h>

static void print_base_info(const struct stat *st);
static const char *get_type(long long mode);

int main(int argc, char **argv)
{
    struct stat st;
    char *target = argv[1];

    if (!target) {
        fputs("Usage: analyze FILE\n", stderr);
        return 1;
    }

    if (lstat(target, &st) < 0) {
        perror(target);
        return 1;
    }

    print_base_info(&st);
    if (S_ISLNK(st.st_mode)) {
        int is_dang = (stat(target, &st) < 0) ? 1 : 0;
        printf("\nThis link %s\n", is_dang ? "is dangling" :
                                           "pointed to a file . . .");
        if (!is_dang)
            print_base_info(&st);
    }
    return 0;
}

static void print_base_info(const struct stat *st)
{
    printf("This file is a %s:\n", get_type(st->st_mode));
    printf("place ID of device: %ld\n", st->st_dev);
    printf("have a %ld index node\n", st->st_ino);
    printf("have a %o(in octal) modes\n", st->st_mode);
    printf("have a %ld hard links\n", st->st_nlink);
    printf("have a %d id of user\n", st->st_uid);
    printf("have a %d id of main group\n", st->st_gid);
    printf((S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode)) ?
           "have a %ld ID device in system\n" :
           "", st->st_rdev);

    printf("have a %ld size in bytes\n", st->st_size);
    printf("have a %ld size of block size in this file system\n", st->st_blksize);
    printf("have a %ld blocks of 512 bytes(sic!)\n", st->st_blocks);
    printf("have a %ld in sec last access to the file\n", st->st_atime);
    printf("have a %ld in sec last modification to the file\n", st->st_mtime);
    printf("have a %ld in sec last modification metadata this file\n", st->st_ctime);
}

static const char *get_type(long long mode)
{
    switch (mode & S_IFMT) {
    case S_IFDIR:  return "directory";
    case S_IFCHR:  return "character device";
    case S_IFBLK:  return "block device";
    case S_IFREG:  return "regular file";
    case S_IFIFO:  return "FIFO/pipe";
    case S_IFLNK:  return "symlink";
    case S_IFSOCK: return "socket";
    default:       return "unknown?";
    }
}
