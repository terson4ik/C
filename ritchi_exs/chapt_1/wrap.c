#include <stdio.h>
/* example
 * MAXWIDTH = 3; 
 * input: "1 2 3 4 5 6 7"
 * "1_2" it's 3 + '\0'; then arr must be MAXWIDTH + 1
 * 2 is last word, and in front of it have space, then remove this space
 * that is in [1] index set '\0' and 2 save to buffer
 * print 1 and write 2 in [0] index of arr of chars
 * next read another portion chars from stdInput:
 * "2_3" again -> 3 last, and in front of it have space:
 * 3 -> buffer, and "2\0". ok
 * 1
 * 2
 * 3
 * ..........................................
 * good. next case:
 * if have input "123456" then
 * 123 write, don't push to buffer because don't have spaces
 * IMPORTANT: buffer[0] have '\0'
 * next read 456, again don't have spaces, then write 456. ok
 * 123
 * 456
 * EOF
 * ............................................
 * if input like this "     yolo           " then we print they like this
 * "yolo"
 * "        "
 * ...............
 * functions for read chars have specific work, it's returns value write chars
 * !!!!!!!and if limit have 1, they write '\0' into limit + 1!!!!!!!
 * main function have
 * while(read part of data, if 0 then EOF
 *       function will return length of writed bytes include '\n')
 *       signature off func is (char buff[] and limit to write chars)
 *       NEED TO OFFSET in case ' ' that is wrap
 *       (length = line(buf + offset, lim - offset)
 * if length == MAXWIDTH and arr[MAX] no have '\n' then it's part of string
 *      call function(extra buffer[] for wrap case, buffer[] with read bytes
 *      wrap case if have at least one space)
 *      after this print common buffer[] 
 *      offset = strlen of extra buffer[];
 *      !!!!!!!!!!!!!after call func buffer have '\0', NO '\n'!!!!!!!!!!!!!!!
 *      then printf('%s\n');
 * else if in this case all fine, \n finded, then is general string
 *      printf("%s");
 *  endLoop
 *  -------------------------------
 *  prototype for cut_tail(dest, src)
 *  int remember = -1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *  need to 2 states -- IN word, and OUT the word
 *  run in begin word
 *  if find char of letter then remember it
 *  -------------
 *  if not find then only spaces or one word, return control up
 *  else write last word to extra buff[];
 *  remove spaces in cycle:
 *  --index of last char
 *  run while index > 0 and while not found commonly letter
 *  stop
 *  ++index and write '\0' to buff[index]
 *  endFunction
 */

/*returns size of success writed bytes in arr,
 * '\0' write to limit + 1 */
int get_line(char *buffer, int limit);

/* cut last word, write it to destination and write '\0' after penultimate 
 * word in the source array. '\n' write manually 
 * or just return full src, but empty dest if case of one word or only space*/
void cut_last(char *destination, char *source);
int str_len(const char *s); /* return before '\0' */
void str_copy(char *destination, const char *source); /* return before '\0' */

#define MAXWIDTH    3
int main(void)
{
    int length, offset;
    char buf[MAXWIDTH + 1];     /* + 1->'\0' count */
    /*extra will contained last word if needs, and write it's to start buff*/
    char extra[MAXWIDTH + 1];   /* + 1->'\0' count */

    offset = 0;
    while((length = get_line(buf + offset, MAXWIDTH - offset))) {
        if(length == MAXWIDTH - offset && buf[MAXWIDTH] != '\n') {
            cut_last(extra, buf);
            /*     '\n`v because cut_lust() write only zero without '\n' */
            printf("%s\n", buf);
            offset = str_len(extra);
            if(offset) {
                str_copy(buf, extra);
            }
        } else {
            offset = 0;
            printf("%s", buf);
        }
    }
    return 0;
}

#define IN  1
#define OUT 0
void cut_last(char *dest, char *src)
{
    int state, lw, nw, i, j;

    nw = -1; 
    state = OUT;
    for(i = 0; src[i]; ++i) {
        if(state ==OUT && src[i] !=' ' && src[i] !='\t' && src[i] !='\n') {
            state = IN;
            ++nw;
            lw = i;
        } else if(state ==IN &&(src[i] ==' ' || src[i] =='\t' ||
                                                src[i] =='\n')) {
            state = OUT;
        }
    }
    if(nw < 0) { /* only spaces */
        dest[0] = '\0';
        return;
    } else if(nw == 0) { /* if nw == 0 then nothing to copy */
        dest[0] = '\0';
    } else {
        str_copy(dest, src + lw);
    }
    /* cut tail */
    if(nw != 0) {
        for(--lw; lw >= 0 && (src[lw] ==' ' || src[lw] =='\t' || src[lw] =='\n'); --lw) {
        }
        src[lw + 1] = '\0';
    } else {
        for(--i; i >= 0 && (src[i] ==' ' || src[i] =='\t' || src[i] =='\n'); --i) {
        }
        src[i + 1] = '\0';
    }
    /* if have "head" of spaces then remove it */
    for(i = 0; src[i] == ' ' || src[i] == '\t' || src[i] == '\n'; ++i) {
    }
    if(i == 0)
        return;
    for(j = 0; src[i]; ++j, ++i)
        src[j] = src[i];
    src[j] = '\0';
}

int get_line(char *buf, int lim)
{
    int c, i;
    for(i = 0; i < lim && (c = getchar()) != EOF; ++i) {
        buf[i] = c;
        if(c == '\n') {
            ++i;
            break;
        }
    }
    buf[i] = '\0';
    return i;
}

void str_copy(char *dest, const char *src)  /* return before '\0' */
{
    int i;
    for(i = 0; (dest[i] = src[i]); ++i) {
    }
}

int str_len(const char *s)  /* return before '\0' */
{
    const char *t = s;
    for(; *t; ++t) {
    }
    return t - s;
}
