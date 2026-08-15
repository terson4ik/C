/* input text in C language; output = define will completed, 
 * ignoring marco() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mhash.h"

int get_word(char *space, char *word, int lim_spc, int lim_wrd);
void get_macro_line(char *definition, int lim);
void skip_quotes(void);
void skip_comment(char c);

#define BUF_SIZE 2048
#define HASH_SIZE 2048
// EOF will defined in stdio, but i don't have parser for include
#define EOF -1

int main(void)
{
#define BUF_SIZE 4048
    struct nlist **hashtab = malloc(sizeof(struct nlist *) * HASH_SIZE);
    char *spaces = malloc(BUF_SIZE);
    char *word = malloc(BUF_SIZE);
    char *complete;
    char c;
    map_init(hashtab, HASH_SIZE);
    
    while (get_word(spaces, word, BUF_SIZE, BUF_SIZE) != EOF)
        switch(*word) {
            case '#': /* simple version: don't handling IF, INCLUDE, etc. */
                get_word(NULL, word, 0, BUF_SIZE);
                if (strcmp(word, "define") == 0) {
                    get_word(NULL, word, 0, BUF_SIZE);
                    get_macro_line(spaces, BUF_SIZE);
                    map_install(word, spaces, hashtab, HASH_SIZE);
                } else if (strcmp(word, "undef") == 0) {
                    get_word(NULL, word, 0, BUF_SIZE);
                    map_undef(word, hashtab, HASH_SIZE);
                } else {
                    while ((c = getchar()) != EOF && c != '\n')
                        ;
                    if (c == '\n')
                        putchar('\n');
                }
                break;
            case '/':
                c = getchar();
                if (c == '*' || c == '/')
                    skip_comment(c);
                else
                    printf("%s%s%c", spaces, word, c);
                break;
            case '\"':
                fputs(spaces, stdout);
                skip_quotes();
                break;
            case '\'':
                fputs(spaces, stdout);
                putchar('\'');
                while((c = getchar()) != EOF) {
                    putchar(c);
                    if (c == '\\')
                        putchar(getchar());
                    else if (c == '\'')
                        break;
                }
                break;
            case '\\':
                printf("%c%c", '\\', getchar());
                break;
            default:
                complete = map_lookup_key(word, hashtab, HASH_SIZE);
                printf("%s%s", spaces, complete ? complete : word);
                break;
        }

    map_erase(hashtab, HASH_SIZE);
    free(spaces);
    free(word);
    free(hashtab);
    return 0;
}

int get_word(char *space, char *word, int lim_spc, int lim_wrd)
{
    char *w = word;
    int c;
    if (lim_spc) {
        while (--lim_spc > 0 && ((c = getchar()) == ' ' || c == '\t'))
            *space++ = c;
        *space = '\0';
    } else
        while ((c = getchar()) == ' ' || c == '\t')
            ;
    *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;   /* EOF */
    }
    while (--lim_wrd > 0 && (isalnum(c = getchar()) || c == '_'))
        *w++ = c;
    *w = '\0';
    ungetc(c, stdin);
    return *word;
}

void get_macro_line(char *definition, int lim)
{
    int c;
    while ((c = getchar()) != EOF && (c == ' ' || c == '\t'))
        ;
    ungetc(c, stdin);

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        if (c == '\\')
            getchar(); /* skip new line if is need */
        else
            *definition++ = c;
    *definition = '\0';
}

void skip_quotes(void)
{
    int c;
    putchar('\"');
    while ((c = getchar()) != EOF && c != '\"')
        putchar(c);
    putchar(c);
}

void skip_comment(char chr)
{
    int c;
    if (chr == '/')
        while ((c = getchar()) != EOF && c != '\n')
        ;
    else if (chr == '*') {
        int prev = '/';
        while ((c = getchar()) != EOF)
            if (prev == '*' && c == '/')
                return;
            else
                prev = c;
    }
}
