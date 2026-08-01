#include <stdio.h> /* for NULL */
#include "alloc.h"

/* Emulate heap. I can't allocate in random place */
#define PTR_MAX_SIZE    10000
#define CHR_MAX_SIZE    MAX_LINE * PTR_MAX_SIZE

#define EDGE    -1

static char *ptrs[PTR_MAX_SIZE];
static char **p_ptr = ptrs;

static char chrs[CHR_MAX_SIZE] = { 0 };
static char *p_chr = chrs;

char *chr_alloc(unsigned int size)
{
    if (((chrs + CHR_MAX_SIZE) - p_chr >= size) && size <= MAX_LINE) {
        *(p_chr + size) = EDGE;
        p_chr += MAX_LINE;
        return p_chr - MAX_LINE;
    } else
        return NULL;
}

void chr_free(char *p)
{
    if (p >= chrs && p < (chrs + CHR_MAX_SIZE))
        p_chr = p;
}

char *chr_realloc(char *p, unsigned int size)
{
    if (size > MAX_LINE)
        return NULL;
    *(p + chr_get_cur_size(p)) = '\0';
    *(p + size) = EDGE;
    return p;
}

int chr_get_cur_size(const char *p)
{
    const char *tmp;
    int lim;
    if (p >= chrs && p < (chrs + CHR_MAX_SIZE)) {
        for (tmp = p, lim = 0; lim < MAX_LINE && *tmp != EDGE; tmp++, lim++) {
        }
        if (!(lim < MAX_LINE) && *tmp != EDGE)
            return 0;
        else
            return tmp - p;
    }else
        return 0;
}

char **ptr_alloc(unsigned int size)
{
    if ((ptrs + PTR_MAX_SIZE) - p_ptr > size) {
        p_ptr += size;
        return p_ptr - size;
    } else
        return NULL;
}

void ptr_free(char **p)
{
    if (p >= ptrs && p < (ptrs + PTR_MAX_SIZE))
        p_ptr = p;
}
