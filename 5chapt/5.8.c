#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef STOLYAROV
#  define STOLYAROV 1
#endif

#if STOLYAROV
static size_t strlen(const char *s);
static int strcmp(const char *s1, const char *s2);
static char *strcpy(char *dst, const char *src);
static char *strcat(char *head, const char *tail);
static char *strdup(const char *src);
static void *my_realloc(void *adr, size_t new_size);
#  define realloc(adr, size) my_realloc(adr, size)
#else
#  include <string.h>
#endif

#define VEC_INIT_SIZE 255u
typedef struct {
    /* storage data like "./hello/word/"<--'/' automatically add in push */
    char *str;
    size_t cur_len, max_len;
} my_vector;

static my_vector *vector_init(unsigned int init_size);

/* automatically add '/' */
static int vector_push(my_vector *v, const char *str);
static const char *vector_get(my_vector *v);
static void vector_destroy(my_vector **v);

static int find(const char *path, const char *target);

int main(int argc, char **argv)
{
    if (argc < 2) {
        fputs("No target argument to run find\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find("./", argv[1]))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

#define CLS_DIR_AND_EXIT(d) do { closedir(d); return 0; } while (0)
#define CLS_DIR_VEC_AND_EXIT(d, v) do { vector_destroy(&v); closedir(d); \
                                        return 0; } while (0)
static int find(const char *path, const char *target)
{
    DIR *dir;
    struct dirent *dent;
    my_vector *cur_path;

    dir = opendir(path);
    if (!dir) {
        perror(path);
        return 1; /* non critical situation */
    }

    cur_path = vector_init(VEC_INIT_SIZE);
    if (!cur_path)
        CLS_DIR_AND_EXIT(dir);

    if (!vector_push(cur_path, path))
        CLS_DIR_VEC_AND_EXIT(dir, cur_path);

    while ((dent = readdir(dir)) != NULL) {
        struct stat st;
        char *full;

        if (strcmp("..", dent->d_name) == 0 || strcmp(".", dent->d_name) == 0)
            continue;

        full = malloc(strlen(vector_get(cur_path)) + strlen(dent->d_name)+1);
        if (!full) {
            perror("malloc");
            CLS_DIR_VEC_AND_EXIT(dir, cur_path);
        }
        sprintf(full, "%s%s", vector_get(cur_path), dent->d_name);

        /* default stat go to link; default find not doing this; use LINKstat */
        if (lstat(full, &st) < 0) {
            perror(full);
            free(full);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            char is_ok = find(full, target);
            free(full);
            if (!is_ok)
                CLS_DIR_VEC_AND_EXIT(dir, cur_path);
            continue;
        }

        if (strcmp(target, dent->d_name) == 0)
            printf("%s\n", full);
        free(full);
    }

    vector_destroy(&cur_path);
    closedir(dir);
    return 1;
}

static my_vector *vector_init(unsigned int init_size)
{
    my_vector *new = malloc(sizeof(*new));
    if (!new) {
        perror("malloc");
        return NULL;
    }
    
    new->str = malloc(init_size);
    if (!new->str) {
        perror("malloc");
        free(new);
        return NULL;
    }

    new->cur_len = 0;
    new->max_len = init_size;
    new->str[0] = '\0';

    return new;
}

static int vector_push(my_vector *v, const char *str)
{
    size_t len = strlen(str);
    char need_slash = (str[len-1] == '/') ? 0 : 1;

    v->cur_len += len + need_slash;
    if (v->cur_len >= v->max_len) {
        char *new_ptr;
        v->max_len *= 2;
        new_ptr = realloc(v->str, v->max_len);
        if (!new_ptr) {
            perror("malloc");
            return 0;
        }
        v->str = new_ptr;
    }

    strcat(v->str, str);
    if (need_slash) {
        v->str[v->cur_len-1] = '/';
        v->str[v->cur_len] = '\0';
    }

    return 1;
}

static const char *vector_get(my_vector *v)
{
    return v->str;
}

static void vector_destroy(my_vector **v)
{
    free((*v)->str);
    free(*v);
    *v = NULL;
}

#if STOLYAROV
static size_t strlen(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r-s;
}

static int strcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
        if (*s1 == 0)
            return 0;
    return (unsigned char)*s1 - (unsigned char)*s2;
}

static char *strcpy(char *dst, const char *src)
{
    char *r = dst;
    while ((*r++ = *src++))
    {}
    return dst;
}

static char *strcat(char *head, const char *tail)
{
    char *r = head;

    /* don't use strlen; empty str give bug */
    while (*r)
        r++;

    strcpy(r, tail);

    return head;
}

static char *strdup(const char *src)
{
    char *new = malloc(strlen(src) + 1);
    if (!new)
        return NULL;

    strcpy(new, src);
    return new;
}

static void *my_realloc(void *adr, size_t new_size)
{
    char *prev = adr;
    char *new  = malloc(new_size);
    if (!new)
        return NULL;

    strcpy(new, prev);
    free(prev);
    return new;
}
#endif
