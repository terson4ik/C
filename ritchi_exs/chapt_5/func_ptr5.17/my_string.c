#include <stdlib.h> /* atof */
#include "my_string.h"

#define TO_LOWER(C)  (((C) >= 'A' && (C) <= 'Z') ? (C) - 'A' + 'a' : (C))
#define TO_UPPER(c)  (((c) >= 'a' && (c) <= 'z') ? (c) - 'a' + 'A' : (c))
#define IS_LETTER(chr)  (((chr) >= 'A' && (chr) <= 'Z')  \
                      || ((chr) >= 'a' && (chr) <= 'z'))
#define IS_DIGIT(chr)    ((chr) >= '0' && (chr) <= '9')
#define IS_SPACE(chr)    ((chr) == ' ' || (chr) == '\t' || (chr) == '\n')
#define ERR_VAL -1

int my_numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
        s1++, s2++;
    return *s1 - *s2;
}

int dir_cmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0') {
        int is_dir1 = IS_DIGIT(*s1) || IS_LETTER(*s1) || IS_SPACE(*s1);
        int is_dir2 = IS_DIGIT(*s2) || IS_LETTER(*s2) || IS_SPACE(*s2);
        if (is_dir1 && is_dir2) {
            if (*s1 == *s2) {
                s1++, s2++;
                continue;
            } else
                break;
        }
        s1 += is_dir1 ? 0 : 1;
        s2 += is_dir2 ? 0 : 1;
    }
    while (*s1 != '\0' && !(IS_DIGIT(*s1) || IS_LETTER(*s1) || IS_SPACE(*s1)))
        s1++;
    while (*s2 != '\0' && !(IS_DIGIT(*s2) || IS_LETTER(*s2) || IS_SPACE(*s2)))
        s2++;
    return *s1 - *s2;
}

int dir_case_cmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0') {
        int is_dir1 = IS_DIGIT(*s1) || IS_LETTER(*s1) || IS_SPACE(*s1);
        int is_dir2 = IS_DIGIT(*s2) || IS_LETTER(*s2) || IS_SPACE(*s2);
        if (is_dir1 && is_dir2){
            if(TO_LOWER(*s1) == TO_LOWER(*s2)) {
                s1++, s2++;
                continue;
            } else
                break;
        }
        s1 += is_dir1 ? 0 : 1;
        s2 += is_dir2 ? 0 : 1;
    }
    while (*s1 != '\0' && !(IS_DIGIT(*s1) || IS_LETTER(*s1) || IS_SPACE(*s1)))
        s1++;
    while (*s2 != '\0' && !(IS_DIGIT(*s2) || IS_LETTER(*s2) || IS_SPACE(*s2)))
        s2++;
    return TO_LOWER(*s1) - TO_LOWER(*s2);
}

int my_strcasecmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && TO_LOWER(*s1) == TO_LOWER(*s2))
        s1++, s2++;
    return TO_LOWER(*s1) - TO_LOWER(*s2);
}

int extract_fild(char *buf, const char *orig_s, int field)
{
    int nw = 0;
    *buf = '\0';
    do {
        const char *start_word;
        while (IS_SPACE(*orig_s))
            orig_s++;
        if (*orig_s != '\0') {
            nw++;
            start_word = orig_s;
        } else
            return ERR_VAL;
        
        if (nw >= field) {/* > for case if field == 0 or negative */
            while (!IS_SPACE(*start_word) && *start_word != '\0')
                *buf++ = *start_word++;
            *buf = '\0';
            return nw;
        } else
            while (!IS_SPACE(*orig_s) && *orig_s != '\0')
                orig_s++;
    } while (*orig_s != '\0');
    return ERR_VAL;
}
void my_str_cpy(char *dst, const char *src) 
{
    while ((*dst++ = *src++)) { /* If zero meet == break */
    }
}