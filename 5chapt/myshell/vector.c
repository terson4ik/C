#include <stdio.h> /* EOF only */
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"

struct vector_tag {
    char *buf;
    size_t cur_len, max_len;
}; /* typedef in header */

static int smart_realoc(vector *v);

vector *vector_init(size_t init_size)
{
    vector *new = malloc(sizeof(*new));
    if (!new)
        return NULL;

    new->buf = malloc(init_size);

    if (!new->buf) {
        free(new);
        return NULL;
    }

    new->buf[0]  = '\0';
    new->cur_len = 0;
    new->max_len = init_size;
    return new;
}

/* if ok return c, else -1 */
int vector_push_c(vector *v, int c)
{
    if (c == EOF)
        return -1;

    if (v->cur_len+1 >= v->max_len)
        if(smart_realoc(v) == -1)
            return -1;

    v->buf[v->cur_len++] = c;
    v->buf[v->cur_len]   = '\0';
    return c;
}

/* if error return -1 */
int vector_push_str(vector *v, const char *s)
{
    v->cur_len += mstrlen(s);
    if (v->cur_len >= v->max_len)
        if(smart_realoc(v) == -1)
            return -1;

    mstrcat(v->buf, s);
    return 1;
}

char *vector_get_str(vector *v)
{
    return v->buf;
}

int vector_buf_is_empty(vector *v)
{
    return v->buf[0] == '\0';
}

void vector_buf_reset(vector *v)
{
    v->buf[0]  = '\0';
    v->cur_len = 0;
}

void vector_dispose(vector *v)
{
    free(v->buf);
    free(v);
}

static int smart_realoc(vector *v)
{
    char *ptr;
    v->max_len = (v->cur_len+1) * 2;
    ptr = mstr_realloc(v->buf, v->max_len);
    if (!ptr)
        return -1;
    v->buf = ptr;
    return 0;
}
