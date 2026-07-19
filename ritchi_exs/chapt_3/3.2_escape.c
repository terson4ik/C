#include <stdio.h>


char *escape(char s[], char t[]);
char *escape_reverse(char s[], char t[]);
int str_size(const char s[]);
#define TEST_SIZE   4096
int main()
{
    int c, i;
    char inp_str[TEST_SIZE], res_str[TEST_SIZE];

    i = 0;
    while ((c = getchar()) != EOF)
        inp_str[i++] = c;
    inp_str[i] = '\0';

    printf("%s", escape(res_str, inp_str));
    puts("\n-----------------------------------------------");
    printf("%s", escape_reverse(inp_str, res_str));
}
    
int str_size(const char s[])
{
    const char *t;
    for (t = s; *t; t++) {
    }
    return t - s;
}
char *escape(char s[], char t[])
{
    int i, j;
    for (j = i = 0; t[i]; i++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
    return s;
}
char *escape_reverse(char s[], char t[])
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\\':
                    switch (t[i+1]) {
                        case 'n':
                            s[j++] = '\n';
                            break;
                        case 't':
                            s[j++] = '\t';
                            break;
                        case '\0':
                            s[j++] = '\\';
                            break;
                        default:
                            s[j++] = '\\';
                            s[j++] = t[i+1];
                            break;
                    }
                    i++;
/*
                    if(t[i+1] == 'n')
                        s[j++] = '\n';
                    else if (t[i+1] == 't')
                        s[j++] = 
*/
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
    return s;
}
