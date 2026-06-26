#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *target;
    
    if(argc < 2) {
        fprintf(stderr, "example of use: ./a.out file.txt\n");
        return 1;
    }

    target = fopen(argv[1], "w");
    if(!target) {
        perror(argv[1]);
        return 2;
    }
    fprintf(target, "Humpty Dumpty sat on a wall,\n"
                    "Humpty Dumpty had a great fall;\n"
                    "All the king\'s horses and all the king\'s men\n"
                    "Couldn\'t put Humpty together again.\n");

    fclose(target); /* by default, fclose use fflush automatically */
    return 0;
}
