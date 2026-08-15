#ifndef MY_HASH_H
#define MY_HASH_H

struct nlist {
    struct nlist *next;
    char *key_word_def;
    char *complete;
};

unsigned int map_hash(const char *s, struct nlist *tab[], unsigned int size);
void map_init(struct nlist *map[], int size);
char *map_lookup_key(const char *s, struct nlist *tab[], unsigned int size);
struct nlist *map_lookup(const char *s, struct nlist *tab[], unsigned int size);
void map_install(const char *name, const char *defn, struct nlist *tab[], 
                                                    unsigned int size);
void map_undef(const char *name, struct nlist *tab[], unsigned int size);
void map_erase(struct nlist *map[], int size);

#endif
