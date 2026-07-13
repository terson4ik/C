/* print a histogram frequency of every char */
#include <stdio.h>

#define MIN_CHAR ' ' /* in ASCII, space minimum char that can see */
#define MAX_CHAR '~' /* ----------tilde maximum ------------------*/
#define DIAPASON (MAX_CHAR - MIN_CHAR + 1)
#define BAR_CHAR '*'

int main()
{
    int i, c;
    int freq_chr[DIAPASON];

    /* array zeroing */
    for(i = 0; i < DIAPASON; ++i)
        freq_chr[i] = 0;

    /* filling array from std input */
    while((c = getchar()) != EOF)
        /* if `c` is visible symbol then */
        if(c >= MIN_CHAR && c <= MAX_CHAR)
            ++freq_chr[c - MIN_CHAR];
    
    /* printing histogram */
    for(i = 0; i < DIAPASON; ++i)
        if(freq_chr[i]) {
            int j;
            printf("'%c':", i + MIN_CHAR);
            for(j = freq_chr[i]; j; --j)
                putchar(BAR_CHAR);
            putchar('\n');
        }

    return 0;
}
