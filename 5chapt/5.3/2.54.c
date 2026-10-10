#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
size_t str_len(const char *s);

#define INT_WIDTH 4
int main(int argc, char **argv)
{
    FILE *fresult;
    int i;

    argc--;
    if (argc < 2) {
        char msg[] = "At least 2 parameters needed\n";
        write(STDERR_FILENO, msg, sizeof(msg)-1);
        return 1;
    }

    fresult = fopen(argv[argc], "w");
    if (!fresult) {
        perror(argv[argc]);
        return 2;
    }

    for (i = 1; i < argc; i++) {
        int count, max, min, buf, reads;
        char *cur_name = argv[i];
        int fd = open(cur_name, O_RDONLY);
        if (fd < 0) {
            perror(cur_name);
            fclose(fresult);
            return 3;
        }

        max = INT_MIN;
        min = INT_MAX;
        count = 0;
        while ((reads = read(fd, &buf, INT_WIDTH)) > 0) {
            if (reads < INT_WIDTH) {
                fprintf(stderr, "%s: incorrect format of data\n", cur_name);
                fclose(fresult);
                return 4;
            }
            count++;
            max = (max < buf) ? buf : max;
            min = (min > buf) ? buf : min;
        }
        if (reads < 0) {
            fprintf(stderr, "%s: error in reading", cur_name);
            fclose(fresult);
            return 5;
        }
        if (!count)
            max = min = 0;
        fprintf(fresult, "%s: total: %d; max value: %d; min value: %d\n",
                cur_name, count, max, min);

        close(fd);
    }

    fclose(fresult);
    return 0;
}
