#include <stdio.h>

#define MAX_SIZE 80

int get_line(char buffer[], int limit);
void print_line();

int main()
{
    int length;
    char str[MAX_SIZE + 2]; /* '\0' + 1 because > 80, not >= 80 */

    while((length = get_line(str, MAX_SIZE + 1)) != 0)
        if(length > MAX_SIZE) {
            printf("%s", str);
            print_line();
        }
    
    return 0;
}

/* if limit 1 then '\0' write in buf[limit] */
int get_line(char buf[], int lim)
{
    int i, c;
    for(i = 0; i<lim && (c = getchar()) !=EOF; ++i)
        if(c == '\n') {
            buf[i] = '\n';
            ++i;
            break;
        } else
            buf[i] = c;

    buf[i] = '\0';
    return i;
}

void print_line()
{
    int c;
    while((c = getchar()) != EOF) {
        putchar(c);
        if(c == '\n')
            break;
    }
}
