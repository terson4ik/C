/* Difficult descriptions: arrays */
struct item { /* wrapper */
    int x, y;
};

int main(void)
{

    /* task conditions: */
    int arrA[245][12];
    double arrB[100][10][2];
    char arrC[5][5];
    char *arrD[5][5];
    struct item *arrE[20][3];
    struct item *arrF[20];

    /* my solution: */
    int (*pA)[12] = arrA;
    double (*pB)[10][2] = arrB;
    char (*pC)[5] = arrC;
    char *(*pD)[5] = arrD;
    struct item *(*pE)[3] = arrE;
    struct item **pF = arrF;

    return 0;
}
