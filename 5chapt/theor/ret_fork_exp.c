#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hello world\n");
    fork();
    return 0;
}
