#include <stdio.h>
a
void string50(FILE *f1, FILE *f2)
{
    char buf[11];
    while(fgets(buf, sizeof(buf), f1)) {
        int i;
        int nlpos = -1;
        for(i = 0; i < sizeof(buf) && buf[i]; ++i)
            if(buf[i] == '\n') {
                nlpos = i;
                break;
            }
        if(nlpos == -1) {
            int c;
            fputc('\n', f2);
            while((c = fgetc(f1)) != EOF)
                if(c == '\n')
                    break;
        } else {
            buf[nlpos] = '\0';
            fprintf(f2, "[%s]\n", buf);
        }
    }
}

int main(int argc, char **argv)
{
    FILE *f1;
    if(argc < 2) {
        fprintf(stderr, "too few arguments");
        return 1;
    }
    f1 = fopen(argv[1], "r");
    if(!f1) {
        perror(argv[1]);
        return 2;
    }
    string50(f1, stdout);
    return 0;
}
