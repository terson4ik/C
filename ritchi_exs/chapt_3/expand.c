#include <stdio.h>

#define IS_DIGIT(arg) ((arg) >= '0' && (arg) <= '9')
#define IS_NUMBER(arg) (((arg) >= 'A' && (arg) <= 'Z') || ((arg) >= 'a' && (arg) <= 'z'))
void expand(const char *s1, char *s2);

#define INIT_SIZE 4096
int main(int argc, char **argv)
{
    char s2[INIT_SIZE];
    if (argc < 2)
        return 1;

    expand(argv[1], s2);
    printf("%s\n", s2);

    return 0;
}

int is_valid_data(char c1, char c2)
{
    if(c2 >= 'a' && c2 <= 'z' && c1 >= 'a' && c1 <= 'z' && c1 >= c2) return 1;
    if(c2 >= 'A' && c2 <= 'Z' && c1 >= 'A' && c1 <= 'Z' && c1 >= c2) return 1;
    if(IS_DIGIT(c2) && IS_DIGIT(c1) && c1 >= c2) return 1;
    return 0;
}

void expand(const char *s1, char *s2)
{
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-' && j > 0 && (IS_NUMBER(s2[j-1]) || IS_DIGIT(s2[j-1]))) {
            if (is_valid_data(s1[i+1], s2[j-1])) {
                int c;
                for (c = s2[j-1] + 1; c <= s1[i+1]; c++, j++)
                    s2[j] = c;
                i++;
            }
        } else
            s2[j++] = s1[i];
    }
    s2[j] = '\0';
}
#if 0
        while ((s2[j] = s1[i]) != '-' && s1[i] != '\0')
            i++, j++;
        j--;
        i++;

        if (j < 0) {
            j += 2;
        } else if (is_valid_data(s1[i], s2[j])) {
            int c;
            for (c = s2[j]; c <= s1[i]; c++)
                s2[j++] = c;
            i++;
        } else {
            j += 2;
            s2[j] = s1[i];
            j++;
            i++;
        }
    }
    s2[j] = '\0';
}
#endif
