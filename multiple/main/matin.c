// マチンの公式により円周率を求める

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "../mulprec2.h"

int main(int argc, char **argv) {
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    printf("pi By matin formula\n");
    printf("number of digits to seek: %d\n", DIGIT);
    Number A, B;
    Number constant;
    setInt(&A, 5);
    arctan(&A, &A);
    setInt(&constant, 16);
    fastMultiple(&A, &constant, &A);
    setInt(&constant, 4);
    setInt(&B, 239);
    arctan(&B, &B);
    fastMultiple(&B, &constant, &B);
    sub(&A, &B, &A);
    divBy10SomeTimes(&A, &A, MARGIN);
    printf("pi = ");
    dispNumberZeroSuppress(&A);
    printf("\n");
    // comparePi(&A);
    printf("piLen = %d\n", getLen(&A));
    printf("program is finished successfully\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("time: %d h %d m %d s\n", (int)(tend - tstart) / 3600,
           (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%fs\n", tend - tstart);
    printf("please press enter key...\n");
    getchar();
    return 0;
}