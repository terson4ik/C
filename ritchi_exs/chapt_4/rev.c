#include <stdio.h>

void reverse(char *s); /* wrapper */
int str_len(const char *s);
#define MAX_LINE 33
int main()
{
    int size;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin)) {
        size = str_len(line) - 1;
        line[size] = (line[size] == '\n') ? '\0' : line[size];
        reverse(line);
        printf("%s\n", line);
    }
    return 0;
}

int str_len(const char *s)
{
    const char *t = s;
    while(*(t++))
        ;
    return t-1 - s;
}
int rec_rev(char *s, int right);
void reverse(char *s)
{
    rec_rev(s, 0);
}
int rec_rev(char *s, int right)
{
    int left, tmp;
    if (s[right] == '\0')
        return 0;
    left = rec_rev(s, right + 1);
    if (left >= right) /* Base case */
        return right; /* Abort all writing */

    tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    return left + 1;
}
