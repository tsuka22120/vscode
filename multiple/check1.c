#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    struct timeval tv;
    double tstart,tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
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

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}