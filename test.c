#include <stdio.h>

void lolka(){
    static int tess = 1;
    printf("%d\n", tess);
    tess++;
}
int main() {
    int x = 28;
    int *p;
    p = &x;
    lolka();
    lolka();
    lolka();
    lolka();
    lolka();
    lolka();
    lolka();
    lolka();
}
