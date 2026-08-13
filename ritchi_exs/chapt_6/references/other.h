#ifndef OTHER_H_SENRY
#define OTHER_H_SENRY

struct get_word_mechanizm_tag {
    char *buf;
    int lim;
    int last_c;
};
typedef struct get_word_mechanizm_tag get_word_mechanizm;

get_word_mechanizm *init_get_word_var(unsigned int size);
void remove_get_word_var(get_word_mechanizm **struct_var);
int get_word(get_word_mechanizm *struct_var);

const char *bin_search(const char *word, const char *words[], int size);

#endif
