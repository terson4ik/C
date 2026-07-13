#include <stdio.h>

#define MAX  300
#define MIN  0
#define STEP 20

double f_to_c(double f);

int main()
{
    double fahr;

    for(fahr = MIN; fahr <= MAX; fahr += STEP)
        printf("%3.0f %-6.1f\n", fahr, f_to_c(fahr));
    return 0;
}

double f_to_c(double fareng)
{
    return (5.0/9.0) * (fareng - 32.0);
}
