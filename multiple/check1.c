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


#if 1
    // sharpの公式により円周率を求める
    Number digitNum;                                 // 求める桁数
    int digit = (KETA * RADIX_LEN) / 2 - RADIX_LEN;  // 求める円周率の桁数
    Number constant;                                 // 定数
    Number x;                                        // 答え
    Number numN;                                     // 回数用多倍長整数
    Number tmp;                                      // 作業用多倍長整数
    Number a, b;                                     // 項a,b
    int n;
    n = 0;
    setInt(&constant, 6);
    setInt(&digitNum, 10);
    fastpower(&digitNum, digit, &tmp);
    // ルート3を求める
    fastpower(&tmp, 2, &digitNum);
    setInt(&tmp, 3);
    multiple(&digitNum, &tmp, &digitNum);
    sqrt_mp(&digitNum, &digitNum);
    // 6ルート3を求める
    multiple(&digitNum, &constant, &constant);
    // 初期値
    clearByZero(&x);
    n = 0;
    printf("完了\n");
    printf("円周率求め中...\n");
    fflush(stdout);
    while (1) {
        setInt(&numN, n);
        // aを求める
        setInt(&a, 2);
        multiple(&a, &numN, &a);
        increment(&a, &a);
        // bを求める
        setInt(&tmp, 3);
        power(&tmp, n + 1, &b);
        // a * bを求める
        if (multiple(&a, &b, &tmp) == -1) {
            printf("overflow\n");
            break;
        }
        // xを求める
        divide(&constant, &tmp, &tmp, NULL);
        if (n % 2 == 0) {
            add(&x, &tmp, &x);
        } else {
            sub(&x, &tmp, &x);
        }
        if (n == digit * 2) {
            break;
        }
        fflush(stdout);
        printf("\r%d", n);
        n++;
    }
    printf("\n");
    dispNumberZeroSuppress(&x);
    printf("\n");
#endif

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %f秒\n", tend - tstart);
    return 0;
}