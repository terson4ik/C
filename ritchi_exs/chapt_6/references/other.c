#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "other.h"
#include "strs.h"

#define NOT_FOUND NULL
#define EMPTY 0

get_word_mechanizm *init_get_word_var(unsigned int size)
{
    get_word_mechanizm *new = malloc(sizeof(*new));
    if (!new)
        return NULL;
    new->buf = malloc(size);
    if (!new->buf)
        return NULL;
    new->lim = size;
    new->last_c = EMPTY;
    return new;
}

void remove_get_word_var(get_word_mechanizm **struct_var)
{
    free((*struct_var)->buf);
    free(*struct_var);
    *struct_var = NULL;
}

int get_word(get_word_mechanizm *struct_var)
{
    int c = (struct_var->last_c == EMPTY) ? getchar() : struct_var->last_c;
    char *w = struct_var->buf;
    int lim = struct_var->lim;

    while (isspace(c) && c != '\n')
        c = getchar();

    *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        struct_var->last_c = EMPTY;
        return c; /* maybe EOF detected */
    }

    while (--lim > 0 && isalpha(c = getchar()))
        *w++ = c;
    *w = '\0';
    struct_var->last_c = c;
    return *(struct_var->buf);
}

const char *bin_search(const char *word, const char *words[], int size)
{
    const char **left = words;
    const char **right = words + size ;
    while (left < right) {
        const char **mid = left + (right - left) / 2;
        int cond = str_cmp(word, *mid);
        if (cond > 0)
            left = mid + 1;
        else if (cond < 0)
            right = mid;
        else
            return *mid;
    }
    return NOT_FOUND;
}
