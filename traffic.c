#include <stdio.h>

    enum lights { 
        green, 
        yellow,
        red 
    } static light = green;
/* 
 * global variable is BAD!!!
 * i know it
*/

/* int because original c don`t have bool */
int beam(enum lights *l) {
    switch(*l) {
        case green:
            printf("all fine, drive forward\n");
            *l = yellow;
            return 1;
        case yellow:
            printf("WARNING!!! Please, brake\n");
            *l = red;
            return 1;
        case red:
            printf("STOP!!!\n");
            *l = green;
            return 0;
        default:
            printf("traffic light is broken\n");
            return 0;
        }
}

void emulation() {
    while(beam(&light))
        ;
    beam(&light);
}

int main() {
    emulation();
    return 0;
}
