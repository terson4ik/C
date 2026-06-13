#include <stdio.h>
#include <string.h>


enum {max_name_len = 64, max_group_len = 8 };

struct student {
    char name[max_name_len];
    char sex;   /* 'm' or 'f' */
    int year_of_birth;
    int major_code;
    int year;
    char group[max_group_len];
    float average;
};
void str_copy(char *dest, const char *src)
{
    int i;
    for(i = 0; (dest[i] = src[i]); ++i) {
    }
}

int main(void)
{
    struct student st1;
    str_copy(st1.name, "Vladyslav Ivanov Otli4nikov");
    st1.sex = 'm';
    st1.year_of_birth = 1995;
    st1.major_code = 51311;
    st1.year = 3;
    str_copy(st1.group, "312");
    st1.average = 4.792;
    struct student st2 = {
        "Rina Astol", 'f', 2000, 51311, 3, "312", 4.792
    };
    struct student st3;
    struct student *p;
    printf("%s, %s\n", st1.name, st2.name);
    memcpy(&st3, &st1, sizeof(struct student));
    p = &st3;
    (*p).year = 2004;
    printf("%d\n", p->year);
    printf("%s, %s, %s\n", st1.name, st2.name, st3.name);
    return 0;
}
