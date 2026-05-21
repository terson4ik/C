#include <stdio.h>

int main()
{
    int i, j;
    int check;
    printf("enter your max value for x*x: ");
    check = scanf("%d", &i);
    if (check != 1) {
        return 1;
    }
    for(j = 1; j <= i; j++)
        printf("%d*%d\t = %d\n", j, j, j*j);
    return 0;
}
