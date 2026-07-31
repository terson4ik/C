#include <stdio.h>

static const char day_tab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int day_of_year(int year, int month, int day)
{ /* year can be negative, it's marked as B.C */
    const char (*pday_tab)[13] = day_tab;
    const char *parr;
    /* TODO: day > 31 */
    if (month > 12 || month < 1 || day < 1 || day > 31)
        return -1;

    pday_tab += (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    parr = *pday_tab;
    
    while (--month > 0) 
        day += *++parr;
    return day;
}

void month_day(int year, int yearday, int *pday, int *pmonth)
{ /* year can be negative, it's marked as B.C */
    const char (*pday_tab)[13] = day_tab;
    const char *parr;
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if ((leap && yearday > 366) || yearday > 365) {
        *pday = -1;
        *pmonth = -1;
        return;
    }

    pday_tab += leap;
    parr = *pday_tab;
    *pmonth = 1;
    while (yearday > *++parr) {
        (*pmonth)++;
        yearday -= *parr;
    }
    *pday = yearday;
}

int main() /* int argc, char **argv */
{
    int d, m;
    month_day(2008, 60, &d, &m);
    printf("%d___%d\n", d, m);
    return 0;
}
