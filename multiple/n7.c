// ハットンの公式を用いて円周率を求めるプログラム

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec2.h"

int main(int argc, char **argv) {
    printf("円周率を%d桁求めます。使用する多倍長整数の桁数:%d\n", DIGIT, KETA);
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    Number constant;  // 定数
    Number x;         // 答え
    Number a, b;      // 項a,b
    clearByZero(&x);
    // 項aを求める
    setInt(&constant, 8);
    setInt(&a, 2);
    arctan(&a, &a);
    multiple(&a, &constant, &a);
    // 項bを求める
    setInt(&constant, 4);
    setInt(&b, 7);
    arctan(&b, &b);
    multiple(&b, &constant, &b);
    // 項a - 項b
    sub(&a, &b, &x);
    divBy10SomeTimes(&x, &x, MARGIN);
    printf("pi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %d 時間 %d 分 %d 秒\n", (int)(tend - tstart) / 3600, (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%f秒\n", tend - tstart);
    return 0;
}