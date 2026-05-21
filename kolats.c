#include <stdio.h>

int kolats(int x)
{
    int count = 0;
    int max = x;
    printf("initial: %d,", x);
    while(x != 1) {
        if(x % 2 == 0)
            x /= 2;
        else
            x = x * 3 + 1;
        if(max < x)
            max = x;
        printf(" %d,", x);
        ++count;
    }
    printf("\b.\n");
    printf("MAX NUMBER IS %d\n", max);
    return count;
}

int main()
{
    int x, check;
    printf("enter the number: ");
    check = scanf("%d", &x);
    if (check != 1)
        return 1;
    printf("total steps = %d\n", kolats(x));
    return 0;
}
