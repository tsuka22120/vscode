// オイラーの公式を用いて円周率を求めるプログラム

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

    Number a, b;      // 項a,b
    Number x;         // 答え
    Number tmp;       // 作業用多倍長整数
    Number constant;  // 定数
    int i;
    setInt(&tmp, 2);
    setInt(&constant, 1);
    mulBy10SomeTimes(&tmp, &tmp, DIGIT + MARGIN);
    multiple(&tmp, &constant, &constant);
    clearByZero(&x);
    i = 0;
    while (1) {
        printf("\r円周率計算%d回試行中", i);
        fflush(stdout);
        factorial(i, &a);
        if (multiple(&a, &constant, &a) == -1) {  // a = 2 * i!
            printf("overflow\n");
            break;
        }
        doubleFactorial(i * 2 + 1, &b);
        divideWithoutRemainder(&a, &b, &a);
        if (isZero(&a)) {
            break;
        }
        add(&x, &a, &x);
        i++;
    }
    printf("\n");
    printf("pi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");
    divBy10SomeTimes(&x, &x, MARGIN);
    printf("pi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %d 時間 %d 分 %d 秒\n", (int)(tend - tstart) / 3600,
           (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%f秒\n", tend - tstart);
    return 0;
}