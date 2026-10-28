#ifndef VECTOR_H_SENTRY
#define VECTOR_H_SENTRY

typedef struct vector_tag vector;

vector *vector_init(size_t init_size);

/* if ok return c, else -1 */
int vector_push_c(vector *v, int c);

/* if error return -1 */
int vector_push_str(vector *v, const char *s);
char *vector_get_str(vector *v);
int vector_buf_is_empty(vector *v);
void vector_buf_reset(vector *v);

void vector_dispose(vector *v);

#endif
