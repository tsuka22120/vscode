// gcc -Wall -o check1.exe multiple/check1.c multiple/mulprec2.c -lm
// で実行できるお！

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "../mt19937ar.h"
#include "../mulprec2.h"

int main(int argc, char **argv) {
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    Number a, b, c, d;
    for (int i = 0; i < 100; i++) {
        setRnd(&a, 150);
        setRnd(&b, 140);
        divideWithoutRemainder(&a, &b, &c);
        divideByInverse(&a, &b, &d);
        if(numComp(&c, &d) != 0) {
            printf("ERROR\n");
            printf("i = %d\n", i);
            dispNumberZeroSuppress(&a);
            printf(" / ");
            dispNumberZeroSuppress(&b);
            printf("\n");
            printf("c = ");
            dispNumberZeroSuppress(&c);
            printf("\n");
            printf("d = ");
            dispNumberZeroSuppress(&d);
            printf("\n");
            break;
        }
    }

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}