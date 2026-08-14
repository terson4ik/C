#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASH_SIZE   101

static struct nlist *hashtab[HASH_SIZE];

unsigned int hash(char *s);

struct nlist *install(char *name,  char *defn);
struct nlist *lookup(char *s);

int main()
{
    struct nlist *tmp;
    char *t = "hello world!";
    char *d = "hi";
    if (!install(d, t))
        return 1;
    tmp = lookup(d);
    if (!tmp)
        return 5;
    printf("define: %s; text: %s\n", tmp->name, tmp->defn);

    return 0;
}

struct nlist *lookup( char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install( char *name,  char *defn)
{
    struct nlist *np;
    unsigned hashval;
    np = lookup(name);
    if (np == NULL) {
        np = malloc(sizeof(*np));
        if (!np)
            return NULL;
        np->name = strdup(name);
        if (np->name == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free(np->defn);
    np->defn = strdup(defn);
    if (np->defn == NULL)
        return NULL;
    return np;
}

unsigned int hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASH_SIZE;
}
