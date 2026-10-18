#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(int argc, char **argv)
{
    char *p, c1, c2;
    int fd; 
    size_t size, i;

    if (argc < 4) {
        fprintf(stderr, "Usage: tr FILE chr1 chr2\n");
        return 1;
    }
    
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror(argv[1]);
        return 1;
    }

    c1 = argv[2][0];
    c2 = argv[3][0];
    size = lseek(fd, 0, SEEK_END);
    p = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror(argv[1]);
        return 1;
    }
    
    for (i = 0; i < size; i++)
        if (p[i] == c1)
            p[i] = c2;

    msync(p, size, MS_SYNC);
    munmap(p, size);
    close(fd);
    return 0;
}
