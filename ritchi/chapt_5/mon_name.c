#include <stdio.h>

char *month_name(int n);
int main() /* int argc, char **argv */
{
    int i;
    for (i = 0; i <= 13; i++)
        printf("%s\n", month_name(i));

    return 0;
}

char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June", "July",
        "August", "September", "October",
        "November", "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}
