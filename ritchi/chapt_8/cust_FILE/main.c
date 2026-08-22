#include "iofiles.h"

int main()
{
    FILE *fp = fopen("iofiles.c", "r"); 
    int c;
    if (!fp)
        return 1;
    while ((c = getc(fp)) != EOF)
        putchar(c);
    _flushbuf('\n', fp);
    return 0;
}
