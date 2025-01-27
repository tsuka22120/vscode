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
    // setInt(&a,1234);
    // inverse2(&a, &a);
    // printf("a = ");
    // dispNumberZeroSuppress(&a);
    // printf("\n");
    // setInt(&b, 1234);
    // setInt(&c, 1);
    // mulBy10SomeTimes(&c, &c, DIGIT + MARGIN);
    // divideWithoutRemainder(&c, &b, &d);
    // printf("d = ");
    // dispNumberZeroSuppress(&d);
    // printf("\n");
    setRnd(&a, 5);
    setRnd(&b, 3);
    setSign(&a, PLUS);
    setSign(&b, PLUS);
    divideWithoutRemainder(&a, &b, &c);
    printf("c = ");
    dispNumberZeroSuppress(&c);
    printf("\n");
    divideByInverse(&a, &b, &d);
    printf("d = ");
    dispNumberZeroSuppress(&d);
    printf("\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}