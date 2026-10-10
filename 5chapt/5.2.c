#include <stdio.h> /* perror only */
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    enum { BUF_SIZE = 4096 };
    char buf[BUF_SIZE];
    ssize_t count;

    while ((count = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        ssize_t writed = 0;
        while (writed != count) {
            ssize_t cur_writed = write(STDOUT_FILENO, buf+writed, count-writed);
            if (cur_writed < 0) {
                perror("In std output");
                return 1;
            }

            writed += cur_writed;
        }
    }

    if (count < 0) {
        perror("In std input");
        return 1;
    }
        
    return 0;
}
