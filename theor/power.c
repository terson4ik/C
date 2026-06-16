#include <stdio.h>

int power(int num, int deg)
{
    int res = 1, i = deg, n = num;
    while(i > 0) {
        if(i % 2 == 1) 
            res *= n;
        n *= n;
        i /= 2;
    }
    return res;
}
int main(void)
{
    int n, i;
    puts("enter 'int' 'degree'");
    if(scanf("%d %d", &i, &n) != 2) {
        perror("fuck you");
        return 1;
    }
    printf("%d\n", power(i, n));
    return 0;
}
