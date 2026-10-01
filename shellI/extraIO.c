#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extraIO.h"

#define IS_EOL(c) ((c) == '\n' || (c) == EOF)

/* typedef in header file */
struct word_tag {
    char *word;
    size_t cur_l, max_l;
};

word *word_init(void)
{
    word *w = malloc(sizeof(*w));
    if (!w)
        return NULL;

    w->word = malloc(BUF_INIT_SIZE);
    if (!w->word) {
        free(w);
        return NULL;
    }

    w->max_l = BUF_INIT_SIZE;
    w->cur_l = 0;

    return w;
}

#define PUSH(stack, val) \
do { \
    *stack = val; \
    stack++; \
} while (0)

enum word_status get_word(word *w)
{
    int c, in_quot = 0;
    char *cur_c = w->word;
    if (!w || !w->word)
        return FATAL_ERR;

    while (isspace(c = getchar()) && !IS_EOL(c)) {
    }

    *cur_c = '\0';
    if (IS_EOL(c)) {
        return EOL;
    } else {
        w->cur_l = 0;
        if (c == '\"') {
            in_quot = 1;
        } else {
            if (c == '\\') {
                c = getchar();
                if (c == EOF)
                    return EOL;
            }
        }
            PUSH(cur_c, c);
            w->cur_l++;
    }

    while (((!isspace(c = getchar())) || (isspace(c) && in_quot)) && !IS_EOL(c)) {
        switch (c) {
        case '\"':
            in_quot = !in_quot;
            continue; /* no break */
        case '\\':
            c = getchar();
            if (c == EOF)
                continue;
            break;
        }

        PUSH(cur_c, c);
        w->cur_l++;

        if (w->cur_l >= w->max_l) {
            w->max_l *= 2;
            w->word = realloc(w->word, w->max_l);
            if (!w->word)
                return FATAL_ERR;
            cur_c = w->word + w->cur_l-1;
        }
    }

    *cur_c = '\0';
    ungetc(c, stdin);
    return in_quot ? QUOT_FAIL : OK;
}

char *word_get_buf(word *w)
{
    return w->word;
}

void word_dispose_struct(word **w)
{
    if (!*w)
        return;

    free((*w)->word);
    free(*w);

    *w = NULL;
}
