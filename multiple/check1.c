// gcc -Wall -o check1.exe multiple/check1.c multiple/mulprec2.c -lm
// で実行できるお！

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec2.h"

int main(int argc, char **argv) {
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    Number a, b,c;
    setInt(&a, 1234567890);
    dispNumber(&a);
    printf("\n");
    mulBy10SomeTimes(&a, &a, 5);
    dispNumber(&a);
    printf("\n");
    // multiple(&a, &b, &c);
    // dispNumber(&c);
    // printf("\n");


    // Number a, b;
    // setInt(&a, 10);
    // fastpower(&a, 20, &b);
    // printf("%p\n", &b);
    // dispNumberZeroSuppress(&b);
    // printf("\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}