/* info dump of characteristics 
 * a) longest argument and its length
 * b) don't repeats
 * c) ONE @ and no less one dot
 * d) only digitals
 * e) similar characters set
 * f) at least one letter
 * g) identify of first arg */

#include <stdio.h>

int str_length(const char *str)
{
    const char *tmp;
    /*              *tmp = 0 = false */
    for(tmp = str; *tmp; tmp++)
    {}

    return tmp - str;
}

const char *check_repeats(const char *str)
{
    int i, j;
    char c;
    if(!str[0])
        return NULL;

    for(i = 0; str[i]; ++i) {
        c = str[i];
        for(j = i + 1; str[j]; ++j) {
            if(c == str[j])
                return NULL;
        }
    }

    return str;
}

const char *check_mail_form(const char *str)
{
    int i, have_dog, have_dot;

    for(have_dog = have_dot = i = 0; str[i]; ++i) {
        if(str[i] == '@') {
            ++have_dog;
        } else if(str[i] == '.') {
            ++have_dot;
        }
    }

    if((have_dog == 1) && have_dot)
        return str;

    return NULL;
}

const char *is_number(const char *str)
{
    int i;

    if(!str[0])
        return NULL;
    for(i = 0; str[i]; ++i) {
        if(str[i] < '0' || str[i] > '9')
            return NULL;
    }

    return str;
}

const char *is_similiar(const char *str)
{
    int i;
    char c;

    if(!str[0])
        return NULL;
    for(i = 0, c = *str; str[i]; ++i) {
        if(c != str[i])
            return NULL;
    }

    return str;
}

const char *have_one_letter(const char *str)
{
    int i;

    for(i = 0; str[i]; ++i) {
        if((str[i] >= 'a' && str[i] <= 'z') ||
           (str[i] >= 'A' && str[i] <= 'Z')) {
           return str;
        }
    }

    return NULL;
}

const char *cmp_general_chars(const char *orig, const char *cmp_str)
{
    int i, j;
    
    for(i = 0; orig[i]; ++i) {
        for(j = 0; cmp_str[j]; ++j) {
            if(orig[i] == cmp_str[j])
                return cmp_str;
        }
    } 

    return NULL;
}

void call_func(char **argv, const char *(*func)(const char*))
{
    int i;
    for(i = 1; argv[i]; ++i) {
            /* if not NULL its true */
        if(func(argv[i]))
            printf("%s ", argv[i]);
    }
}
int main(int argc, char **argv)
{
    /* if just ./prog -- exit */
    if(argc == 1)
        return 0;

    unsigned int tmp, max, i, j;
    /* finding largest word */
                                        /* NULL = false */
    for(i = 2, j = 1, max = str_length(argv[j]); argv[i]; ++i) {
        if(max < (tmp = str_length(argv[i]))) {
            max = tmp;
            j = i;
        }
    }
    printf("a)%s\t%d\n", argv[j], max);
    printf("b)");
    /* i need function which get another function. but i don't now syntax */
    /* chapter 5.11. Thanks Ritchie */
/* qsort: сортировка v[left]...v[right] в порядке возрастания */
    /*void qsort(void *v[], int left, int right,int (*comp)(void *, void *)){ */
    call_func(argv, check_repeats);
    printf("\b\nc)");
    call_func(argv, check_mail_form);
    printf("\b\nd)");
    call_func(argv, is_number);
    printf("\b\ne)");
    call_func(argv, is_similiar);
    printf("\b\nf)");
    call_func(argv, have_one_letter);
    printf("\b\ng)");
    for(i = 2; argv[i]; ++i) {
        if(cmp_general_chars(argv[1], argv[i]))
            printf("%s ", argv[i]);
    }
    printf("\b\n");

    return 0;
}
