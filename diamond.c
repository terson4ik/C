#include <stdio.h>
/*
i = 7
123*
12*1*
1*123*
*12345*
1*123*
12*1*
123*
 */

void print_chars(char c, int i)
{
    int j;
    for(j = 0; j < i; j++)
        printf("%c", c);
}

void draw_diamante(int size)
{
    int row, outs;
    for(row = 1, outs = size / 2; row <= 1 + size / 2; outs--, row++){
        print_chars(' ', outs);
        print_chars('*', 1);
        if(row != 1)
        {
            print_chars(' ', row * 2 - 3);
            print_chars('*', 1);
        }
        printf("\n");
    }
    for(row = 2 + size / 2, outs = 1; row <= size; outs++, row++){
        print_chars(' ', outs);
        print_chars('*', 1);
        if(row != size)
        {
            print_chars(' ', (1 + size - row) * 2 - 3);
            print_chars('*', 1);
        }
        printf("\n");
    }
}

int main()
{
    int x;
    char check;
    printf("enter size for diamante\n");
    check = scanf("%d", &x);
    if(check != 1)
        return 1;
    if(x % 2 != 1)
        return 2;
    draw_diamante(x);   
    return 0;
}
