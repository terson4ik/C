#include <stdio.h>

int main()
{
    /* 25 Dec 1988 */
    int day, year;
    char monthname[20];

    scanf("%d %s %d", &day, monthname, &year);
    printf("%d %s %d\n", day, monthname, year);
    return 0;
}
