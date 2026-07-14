#include <stdio.h>

#define BASE_OF_HEX 16

int htoi(const char *str);

int main(int argc, char **argv)
{
    int i;
    if (argc < 2)
        return 1;
    for (i = 1; i < argc; i++)
        printf("%d\n", htoi(argv[i]));
    return 0;
}
#if 1
int htoi(const char *str)
{
    int n = 0, i;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;
    else
        i = 0;

    for(; str[i]; i++)
        if(str[i] >= '0' && str[i] <= '9')
            n = n * BASE_OF_HEX + str[i] - '0';
        else if(str[i] >= 'A' && str[i] <= 'F')
            n = n * BASE_OF_HEX + str[i] - 'A' + 10;
        else if(str[i] >= 'a' && str[i] <= 'f')
            n = n * BASE_OF_HEX + str[i] - 'a' + 10;
        else {
            fprintf(stderr, "In %s: Invalid input: %c\n", str, str[i]);
            break;
        }

    return n;
}
        
#else
#define IS_HEX_LETTER(x) (((x) >= 'A' && (x) <= 'F') \
                      || (((x) >= 'a' && (x) <= 'f')))
#define IS_DIGIT(x) ((x) >= '0' && (x) <= '9')
#define A_IN_HEX    10
#define NON_HEX_CODE 16
int calc_hex_a(char c);
char upper(char c);
char lower(char c);

char upper(char c)
{
    /* if c = a then a - a + A = A, this is (shift c - a) + target range */
    return c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c;
}

int calc_hex_a(char c)
{
    if (!IS_HEX_LETTER(c))
        return NON_HEX_CODE;
    return upper(c) - 'A' + A_IN_HEX;
}

int htoi(const char *str)
{
    /* "123"; n = 0;
     * n = n * 10 + 1;
     * n = ........ 2*/
    int n = 0;
    int i;

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;
    else
        i = 0;
    while (str[i]) {
        if (IS_DIGIT(str[i]))
            n = n * BASE_OF_HEX + str[i] - '0';
        else {
            int range = calc_hex_a(str[i]);
            if(range > 15) {
                fprintf(stderr, "In %s: Invalid input: %c\n", str, str[i]);
#  if 0
                exit(1);
#  else
                return n;
#endif
            }
            n = n * BASE_OF_HEX + range;
        }
        ++i;
    }
    return n;
}
#endif
