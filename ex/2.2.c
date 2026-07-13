#include <stdio.h>

int main()
{
    int c, i, lim;

    lim = 50;
#if 0
    for(i = 0; (i < lim-1) * ((c = getchar()) != EOF) * (c != '\n'); ++i)
        putchar(c);
#elif 0
    for(i = 0; ;++i)
        if(!(i < lim - 1))
            break;
        else if(!((c = getchar()) != EOF))
            break;
        else if(!(c != '\n'))
            break;
        else
            putchar(c);
#else
    for(i = 0; ;++i)
        if(i >= lim - 1)
            break;
        else if((c = getchar()) == EOF)
            break;
        else if(c == '\n')
            break;
        else
            putchar(c);
#endif
    return 0;
}
