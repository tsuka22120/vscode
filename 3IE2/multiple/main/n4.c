// リーマンのゼータ関数から円周率を求める

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "../pi.h"

int main(int argc, char **argv) {
    printf("円周率を%d桁求めます。使用する多倍長整数の桁数:%d\n", DIGIT, KETA);
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    Number digitNum;  // 求める桁数
    Number x;         // 答え
    Number x0;        // 前の答え
    Number numN;      // 回数用多倍長整数
    Number tmp;       // 作業用多倍長整数
    Number a, b;      // 項a,b
    int n;
    clearByZero(&x0);
    setInt(&digitNum, 10);
    fastpower(&digitNum, DIGIT * 2, &tmp);
    clearByZero(&x);
    setInt(&numN, 1);
    // 分子を設定(固定)
    setInt(&a, 6);
    multiple(&a, &tmp, &a);
    n = 0;
    while(1){
        copyNumber(&b, &numN);
        // 分母を設定
        if(fastpower(&b, 2, &b) == -1){// b = n^2
            printf("overflow\n");
            break;
        }
        // a / b
        divideWithoutRemainder(&a, &b, &b);
        if(isZero(&b)){
            break;
        }
        add(&x, &b, &x);
        increment(&numN, &numN);
        n++;
        printf("\r円周率計算%d回試行中", n);
        fflush(stdout);
    }
    printf("\n");
    printf("pi ^ 2 = ");
    dispNumberZeroSuppress(&x);
    printf("\n");
    sqrt_mp(&x, &x);
    printf("pi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %d 時間 %d 分 %d 秒\n", (int)(tend - tstart) / 3600, (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%f秒\n", tend - tstart);
    return 0;
}