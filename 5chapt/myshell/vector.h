#ifndef VECTOR_H_SENTRY
#define VECTOR_H_SENTRY

typedef struct {
    char *buf;
    size_t cur_len, max_len;
} vector;

vector *vector_init(size_t init_size);

/* if ok return c, else -1 */
int vector_push_c(vector *v, int c);

/* if error return -1 */
int vector_push_str(vector *v, const char *s);
char *vector_get_str(vector *v);
void vector_buf_reset(vecor *v);

void vector_dispose(vector *v);

#endif
