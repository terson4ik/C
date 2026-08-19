/* 7.7) grep */
#include <stdio.h>
#include <stdlib.h>

typedef struct flags_tag {
    /* in feature, 9+ keys, need change char to int or long */
    unsigned char is_invert    : 1;
    unsigned char is_num_lines : 1;
    unsigned char is_ignore_cs : 1;
    unsigned char is_count     : 1;
}flags_struct;

void parse_argv(char **argv, flags_struct *flag, char **pat, char ***flist);
FILE *broot_open(char *name, char *mode); /* abort program */

unsigned int file_search(FILE *src, char *patt, char *fname, flags_struct flag,
                char *(*comp_str)(const char *s1, const char *s2));

char *invert_str_str(const char *s1, const char *s2);
char *invert_str_case_str(const char *s1, const char *s2);
char *(*strfunc_from_flags(const flags_struct flag))(const char *s1, const char *s2);

char *str_str(const char *s1, const char *s2);
char *str_case_str(const char *s1, const char *s2);
char *str_cpy(char *dst, const char *src);
size_t str_len(const char *s);
void *re_alloc(void *legacy_adr, size_t new_size);

#define DEFAULT_BUF_SIZE 100
#define HELP_MSG    "Example of use: grep [OPTIONS] \"pattern\" files\n"
#define FLAGS_MSG   "-n for print numbers\n" \
                    "-v for non matches strings\n" \
                    "-c for print only count of matches\n" \
                    "-i for ignore case\n"

#ifdef isalnum
#undef isalnum
#endif
#define isalnum(c) (((c) >= 'a' && (c) <= 'z') || \
                    ((c) >= 'A' && (c) <= 'Z') || \
                    ((c) >= '0' && (c) <= '9'))
#define to_upper(c) (((c) >= 'A' && (c) <= 'Z') ? ((c) - 'A' + 'a') : (c))

int main(int argc, char **argv)
{
    flags_struct flag = { 0 };
    char **file_list = NULL, *pattern, *last_name;
    char *(*str_cmp_ptr)(const char *, const char *);
    char is_first;
    FILE *fp; /* inits before loop */
    if (argc < 2) {
        fputs(HELP_MSG, stderr);
        return 1;
    }
    parse_argv(argv, &flag, &pattern, &file_list);
    str_cmp_ptr = strfunc_from_flags(flag); 
    last_name = *file_list++;
    fp = (last_name == NULL) ? stdin : broot_open(last_name, "r");
    is_first = 1;
    while (fp) {
        file_search(fp, pattern, ((*file_list || !is_first) ? last_name : NULL),
                flag, str_cmp_ptr);
        if (fp == stdin) /* if no break, stdin will broken */
            break;
        fclose(fp);
        last_name = *file_list++;
        is_first = 0;
        fp = (last_name == NULL) ? NULL : broot_open(last_name, "r");
    }
    return 0;
}

void parse_argv(char **argv, flags_struct *flag, char **pat, char ***flist)
{
    while (*++argv && **argv == '-') {
        char *key = *argv + 1;
        while (isalnum(*key)) {
            switch (*key) {
                case 'n':
                    flag->is_num_lines = 1;
                    break;
                case 'v':
                    flag->is_invert = 1;
                    break;
                case 'i':
                    flag->is_ignore_cs = 1;
                    break;
                case 'c':
                    flag->is_count = 1;
                    break;
                default:
                    fprintf(stderr, "Unknown option: %c\n" FLAGS_MSG, *key);
                    exit(1);
                    break;
            }
            key++;
        }
    }
    if (!*argv) {
        fputs("Bad usage, pattern not founded." HELP_MSG, stderr);
        exit(2);
    }
    *pat = *argv++;
    *flist = argv;
}

unsigned int file_search(FILE *src, char *patt, char *fname, flags_struct flag,
                char *(*comp_str)(const char *s1, const char *s2))
{
    char *buf = malloc(DEFAULT_BUF_SIZE);

    long buf_size = DEFAULT_BUF_SIZE;
    unsigned int matches = 0;
    unsigned int nl = 0;
    long bias = 0;
    while (fgets(buf + bias, buf_size - bias, src) != NULL) {
        bias = str_len(buf);
        if (bias)
            bias--;
        else
            buf[0] = '\0';

        if (buf[bias] != '\n' && !feof(src)) {
            buf_size *= 2;
            buf = re_alloc(buf, buf_size);
            continue;
        }
        nl++;
        if (comp_str(buf, patt)) {
            matches++;
            if (flag.is_count)
                continue;

            if (fname != NULL)
                printf("%s:", fname);
            if (flag.is_num_lines)
                printf("%d:", nl);
            printf("%s", buf);
        }
        bias = 0;
    }
    if (flag. is_count) {
        if (fname != NULL)
            printf("%s:", fname);
        printf("%u\n", matches);
    }
    free(buf);
    return matches;
}

char *invert_str_str(const char *s1, const char *s2)
{
    return str_str(s1, s2) ? NULL : (char *)s1;
}

char *invert_str_case_str(const char *s1, const char *s2)
{
    return str_case_str(s1, s2) ? NULL : (char *)s1;
}

FILE *broot_open(char *name, char *mode)
{
    FILE *new_fp = fopen(name, mode);
    if (!new_fp) {
        perror(name);
        exit(2);
    } else
        return new_fp;
}

char *(*strfunc_from_flags(const flags_struct flag))(const char *s1, const char *s2)
{
    if (flag.is_invert)
        return flag.is_ignore_cs ? invert_str_case_str : invert_str_str;
    else
        return flag.is_ignore_cs ? str_case_str : str_str;
}

char *str_str(const char *s1, const char *s2)
{
    const char *r1, *r2;

    for(r1 = s1; *r1; r1++) {
        const char *tmp1 = r1;
        for (r2 = s2; *tmp1 && *r2 && (*tmp1 == *r2); r2++, tmp1++)
            ;
        if (*r2 == '\0')
            return (char *)r1;
        else if (*tmp1 == '\0')
            return NULL;
    }
    return NULL;
}
char *str_case_str(const char *s1, const char *s2)
{
    const char *r1, *r2;

    for(r1 = s1; *r1; r1++) {
        const char *tmp1 = r1;
        for (r2 = s2; *tmp1 && *r2 && (to_upper(*tmp1) == to_upper(*r2)); r2++, tmp1++)
            ;
        if (*r2 == '\0')
            return (char *)r1;
        else if (*tmp1 == '\0')
            return NULL;
    }
    return NULL;
}

size_t str_len(const char *s)
{
    const char *r = s;
    while (*r)
        r++;
    return r - s;
}

char *str_cpy(char *dst, const char *src)
{
    char *r = dst;
    while ((*r++ = *src++))
        ;
    return dst;
}

void *re_alloc(void *legacy_adr, size_t new_size)
{
    void *new = malloc(new_size);
    str_cpy((char *)new, (const char *)legacy_adr);
    free(legacy_adr);
    return new;
}
