#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    struct NUMBER a, b, c;
    int numA, numB, numC = 1;
    for (int i = 0; i < 10000; i++) {
        setRnd(&a, 4);
        setRnd(&b, 4);
        getInt(&a, &numA);
        getInt(&b, &numB);
        if (multiple(&a, &b, &c) == -1) {
            printf("error\n");
            break;
        }
        getInt(&c, &numC);
        if (numA * numB != numC) {
            printf("numA: %d, numB: %d, numC: %d\n", numA, numB, numC);
            printf("error\n");
            break;
        }
    }

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}