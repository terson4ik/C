#include <stdio.h>
#include <math.h>

int main(void)
{
    FILE *f;
    int angledeg;
    f = fopen("sincos.txt", "w");
    if(!f) {
        perror("sincos.txt");
        return 1;
    }
    for(angledeg = 0; angledeg <= 360; ++angledeg) {
        double rads, s, c;
        rads = (double)angledeg * M_PI / 180;
        s = sin(rads);
        c = cos(rads);
        fprintf(f, "%03d % 7.5f % 7.5f\n", angledeg, s, c);
    }
    fclose(f);
    return 0;
}
