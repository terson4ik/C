#ifndef ALLOC_H_MY 
#define ALLOC_H_MY
#define MAX_LINE        500 /* Emulate heap */
char *chr_alloc(unsigned int size);
char *chr_realloc(char *p, unsigned int size);
int chr_get_cur_size(const char *p);
void chr_free(char *p);

char **ptr_alloc(unsigned int size);
void ptr_free(char **p);

#endif
