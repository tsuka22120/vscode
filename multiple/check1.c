#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    struct NUMBER a,b;
    int r;

    init_genrand((unsigned long)time(NULL));

    setInt(&a, -12345);
    printf("a = ");
    dispNumber(&a);
    printf("\n");

    copyNumber(&b, &a);
    setSign(&b, 1);
    printf("b = ");
    dispNumber(&b);
    printf("\n");

    r = getSign(&b);
    printf("getSign() = %d\n", r);

    r = numComp(&a, &b);
    printf("numComp() = %d\n", r);

    return 0;
}