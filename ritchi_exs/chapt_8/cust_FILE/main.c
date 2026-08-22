#include "iofiles.h"

int main()
{
    FILE *fp = fopen("iofiles.c", "r"); 
    int c, n;
    if (!fp)
        return 1;
    while ((c = getc(fp)) != EOF)
        putchar(c);
    fflush(stdout);
    fclose(fp);
    fp = fopen("iofiles.c", "r"); 
    if (!fp)
        return 1;
    fseek(fp, 9, 0);
    n = 10;
    while (n-- > 0)
        putchar(getc(fp));
    fflush(stdout);
    fclose(fp);
    return 0;
}
