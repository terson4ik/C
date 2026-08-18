#include <stdio.h>

#define MAXLINE 4096

int main()
{
    int day, year, month;
    char line[MAXLINE];
    char monthname[20];

    while (fgets(line, MAXLINE, stdin) != NULL) {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("valid: %s\n", line);
        else if (sscanf(line, "%d/%d/%d", &day, &month, &year) == 3)
            printf("valid: %s\n", line);
        else
            printf("invalid: %s\n", line);
    }
    return 0;
}
