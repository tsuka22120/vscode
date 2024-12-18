#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    time_t st, et;
    st = time(NULL);
    init_genrand((unsigned long)time(NULL));

    // struct NUMBER a, b, c, d;
    // setInt(&a, 322);
    // setInt(&b, 3);
    // divide(&a, &b, &c, &d);
    // dispNumberZeroSuppress(&a);
    // printf(" / ");
    // dispNumberZeroSuppress(&b);
    // printf(" = ");
    // dispNumberZeroSuppress(&c);
    // printf(" ... ");
    // dispNumberZeroSuppress(&d);
    // printf("\n");

    struct NUMBER a, b, c, d;
    int numA, numB, numC, numD;
    for (int i = 0; i < 100000; i++) {
        numA = genrand_int32() % 10000000;
        numB = genrand_int32() % 100 + 1;
        setInt(&a, numA);
        setInt(&b, numB);
        divide(&a, &b, &c, &d);
        getInt(&c, &numC);
        getInt(&d, &numD);
        if (numA / numB != numC || numA % numB != numD) {
            printf("error\n");
            break;
        }
    }

    et = time(NULL);
    printf("time: %ld\n", et - st);
    return 0;
}