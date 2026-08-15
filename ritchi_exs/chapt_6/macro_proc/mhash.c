#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mhash.h"

unsigned int map_hash(const char *s, struct nlist *tab[], unsigned int size)
{
    unsigned hash_sum;
    for (hash_sum = 0; *s; s++)
        hash_sum = *s + 31 * hash_sum;
    return hash_sum % size;
}

void map_init(struct nlist *map[], int size)
{
    for (size--; size >= 0; size--, map++)
        *map = NULL;
}

char *map_lookup_key(const char *s, struct nlist *tab[], unsigned int size)
{
    struct nlist *elem;
    for (elem = tab[map_hash(s, tab, size)]; elem != NULL; elem = elem->next)
        if (strcmp(elem->key_word_def, s) == 0)
            return elem->complete;
    return NULL;
}

struct nlist *map_lookup(const char *s, struct nlist *tab[], unsigned int size)
{
    struct nlist *elem;
    for (elem = tab[map_hash(s, tab, size)]; elem != NULL; elem = elem->next)
        if (strcmp(elem->key_word_def, s) == 0)
            return elem;
    return NULL;
}

void map_install(const char *name, const char *defn, struct nlist *tab[], 
                                                    unsigned int size)
{
    struct nlist *cur;
    cur = map_lookup(name, tab, size);
    if (cur == NULL) {
        unsigned hsum = map_hash(name, tab, size);
        cur = malloc(sizeof(*cur));
        if (!cur)
            return;
        cur->key_word_def = strdup(name);
        if (!cur->key_word_def)
            return;
        cur->complete = strdup(defn);
        if (!cur->complete)
            return;
        cur->next = tab[hsum];
        tab[hsum] = cur;
    } else {
        free(cur->complete);
        cur->complete = strdup(defn);
        if (!cur->complete)
            return;
    }
}

void map_undef(const char *name, struct nlist *tab[], unsigned int size)
{
    struct nlist **p = &tab[map_hash(name, tab, size)];
    struct nlist *cur;
    for (cur = *p; cur != NULL; cur = cur->next)
        if (strcmp(cur->key_word_def, name) == 0) {
            *p = cur->next;
            free(cur->key_word_def);
            free(cur->complete);
            free(cur);
            return;
        } else
            p = &cur->next;
}

void map_erase(struct nlist *map[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        struct nlist *cur;
        struct nlist *next;
        for (cur = map[i]; cur != NULL; cur = next) {
            next = cur->next;
            free(cur->key_word_def);
            free(cur->complete);
            free(cur);
        }
        map[i] = NULL;
    }
}
