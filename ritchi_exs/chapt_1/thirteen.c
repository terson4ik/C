/* printing histograms for frequency length of words in STD_INPUT */
#include <stdio.h>

#define MAX_LEN  15
#define IN_W     1
#define OUT_W    0
#define STAT_BAR '*'

int main()
{
    int i, c, length, state, max_len;
    int freq_len[MAX_LEN];

    /* array zeroing */
    for(i = 0; i < MAX_LEN; ++i)
        freq_len[i] = 0;

    state = OUT_W;
    length = 0;
    /* filling an array */
    while((c = getchar()) != EOF || length) {
        /* if new word */
        if(state == OUT_W && (c != ' ' && c != '\n' && c != '\t' &&
                              c != EOF)) {
            state = IN_W;
            length = 1;

        /* if inside word and not space */
        } else if(state == IN_W && (c != ' ' && c != '\n' && c != '\t' &&
                                    c != EOF))
            ++length;
        /* if end of word, go to generalization length */
        else if(state == IN_W && (c == ' ' || c == '\n' || c == '\t' ||
                                  c == EOF)) {
            state = OUT_W;
            if(length > MAX_LEN)
                length = MAX_LEN;
            ++freq_len[length - 1];
            length = 0;
        }
    }
    /* printing horizontal histogram and find max length */
    for(max_len = i = 0; i < MAX_LEN; ++i) {
        int j;
        /* edge case -- max val */
        if(i + 1 == MAX_LEN)
            printf("%-2d+:", i + 1);
        else
            printf("%-3d:", i + 1);

        /* drawing bar */
        for(j = freq_len[i]; j; --j)
            putchar(STAT_BAR);

        putchar('\n');
        /* find max length */
        if(max_len < freq_len[i])
            max_len = freq_len[i];
    }
    putchar('\n');

    /* printing vertical histogram */
    for(i = max_len; i > 0; --i) {
        int j;
        for(j = 0; j < MAX_LEN; ++j) {
            if(freq_len[j] >= i)
                printf("%c", STAT_BAR);
            else
                putchar(' ');

            if(j > 8)
                printf("  ");
            else
                putchar(' ');
        }
        putchar('\n');
    }
    /* print digitals for vertical histogram */
    for(i = 0; i < MAX_LEN; ++i) {
        if(i + 1 == MAX_LEN)
            printf("%d+ ", i + 1);
        else
            printf("%d ", i + 1);
    }
    putchar('\n');
  
    return 0;
}
