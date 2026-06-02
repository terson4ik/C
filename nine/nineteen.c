#include <stdio.h>

#define OUTWORD 0
#define INWORD  1

int main()
{
    /* working variables */
    int c, last_c, state, word_length, start_A, nspaces;
    char is_have_reason;
    /* results vars */
    int nw, max_spaces, evens, odds, sevens, twos, Az, brackets, ovals;
    unsigned int max, min;

    state = OUTWORD;
    is_have_reason = 0; /* false */
    last_c = nspaces = start_A = word_length = 0;
    brackets = max = Az = sevens = twos = evens = odds = nw = max_spaces = 0;
    ovals = 0;
    min = -1;  /* WARNING: i need MAX for min. min is unsigned, -1 = FFFFF... */
    while((c = getchar()) != EOF) {
        ++is_have_reason;
        if(c == ' ' || c == '\n' || c == '\t') { /* spaces, or nl, no words */
            if(state == INWORD || c == '\n') {
                if(max_spaces < nspaces) {
                    max_spaces = nspaces;
                }
                nspaces = 0;
            }
            if(c != '\n' && (state == OUTWORD || c == ' ' || c == '\t'))
                ++nspaces;
            state = OUTWORD;
            /* if last character be a end of word,
               then calculate new max spaces */
            if(word_length != 0) {
                if(start_A) {
                    if(last_c == 'z')
                        ++Az;
                    start_A = 0;
                }
                if(min > word_length)
                    min = word_length;
                if(max < word_length)
                    max = word_length;
                if(word_length <= 2)
                    ++twos;
                if(word_length > 7)
                    ++sevens;
                if(word_length % 2 == 0) /* it's even */
                    ++evens;
                else
                    ++odds;
                word_length = 0;
            }
            if(c == '\n') { /* if new line then print 
                               and configure vars to next string */
                if(max_spaces < nspaces)
                    max_spaces = nspaces;
                printf("a)%d\n", nw);
                printf("b)%d, %d\n", evens, odds);
                printf("c)%d, %d\n", sevens, twos);
                printf("d)%d\n", Az);
                printf("e)%d, %d, %d\n", nw, max, min == -1 ? 0 : min);
                printf("f)%d, %d\n", max, max_spaces);
                if(brackets == 0)
                    printf("g)YES\n");
                else
                    printf("g)NO\n");
                printf("h)%d\n", ovals);
                is_have_reason = nspaces = start_A = word_length = 0;
                max = Az = sevens = twos = evens = odds = nw = max_spaces = 0;
                ovals = brackets = 0;
                min = -1;  /* WARNING: i need MAX for min.
                              min is unsigned, -1 = FFFFF... */
            }      
        } else { /* if it's part of word, then else */ 
            if(state == OUTWORD) {
                state = INWORD;
                if(c == 'A')
                    ++start_A;
                ++nw;
            }
            /* if first ')' then it`s don't increment */
            if(brackets >= 0 && c == '(')
                ++brackets;
            if(c == ')') {
                if(last_c == '(')
                    ++ovals;
                --brackets;
            }
            ++word_length;
        }
        last_c = c;
    }
    if(is_have_reason) {
        if(max_spaces < nspaces)
            max_spaces = nspaces;
        printf("a)%d\n", nw);
        printf("b)%d, %d\n", evens, odds);
        printf("c)%d, %d\n", sevens, twos);
        printf("d)%d\n", Az);
        printf("e)%d, %d, %d\n", nw, max, min == -1 ? 0 : min);
        printf("f)%d, %d\n", max, max_spaces);
        if(brackets == 0)
            printf("g)YES\n");
        else
            printf("g)NO\n");
        printf("h)%d\n", ovals);
    }
    return 0;
}
