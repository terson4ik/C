#include <stdio.h> 
#include <stdlib.h>

void printd(int x);
int main(int argc, char **argv)
{
    printd(123456);
    putchar('\n');
}

void printd(int n)
{
    if (n < 0) {
        n = -n;
        putchar('-');
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
