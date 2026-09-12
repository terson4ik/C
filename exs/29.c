/* Difficult descriptions: arrays */

/* task conditions: */
void fA() {}
int fB(int t) {}
void *fC(int X) {}
double fD(int x, const char *str) {}
void fE(double (*vecp)[3]) {}
double (*fF(int len, double (*vecp)[3]))[3] {}

int main(void)
{
    /* my solution: */
    void (*pfA)() = fA;
    int (*pfB)(int) = fB;
    void *(*pfC)(int) = fC;
    double (*pfD)(int, const char *) = fD;
    void (*fe)(double (*)[3]) = fE;
    double (*(*pfF)(int, double (*)[3]))[3] = fF;

    return 0;
}
