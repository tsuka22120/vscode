// sharpの公式により円周率を求める

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

    Number digitNum;  // 求める桁数
    Number constant;  // 定数
    Number x;         // 答え
    Number x0;        // 前の答え
    Number numN;      // 回数用多倍長整数
    Number tmp;       // 作業用多倍長整数
    Number a, b;      // 項a,b
    int n;
    n = 0;
    clearByZero(&x0);
    setInt(&constant, 6);
    setInt(&digitNum, 10);
    fastpower(&digitNum, DIGIT, &tmp);
    // ルート3を求める
    fastpower(&tmp, 2, &tmp);
    setInt(&digitNum, 3);
    dispNumberZeroSuppress(&digitNum);
    printf(" * ");
    dispNumberZeroSuppress(&tmp);
    printf(" = ");
    multiple(&tmp, &digitNum, &digitNum);
    dispNumberZeroSuppress(&digitNum);
    printf("\n");
    sqrt_mp(&digitNum, &digitNum);
    printf("root3 = ");
    dispNumberZeroSuppress(&digitNum);
    printf("\n");
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
        fastpower(&tmp, n + 1, &b);
        // a * bを求める
        if (multiple(&a, &b, &tmp) == -1) {
            printf("overflow\n");
            break;
        }
        // xを求める
        if(divideWithoutRemainder(&constant, &tmp, &tmp) == -1) {
            printf("overflow\n");
            break;
        }
        if (n % 2 == 0) {
            if(add(&x, &tmp, &x) == -1) {
                printf("overflow\n");
                break;
            }
        } else {
            if(sub(&x, &tmp, &x) == -1) {
                printf("overflow\n");
                break;
            }
        }
        if (numComp(&x, &x0) == 0) {
            break;
        }
        fflush(stdout);
        printf("\r%d", n);
        copyNumber(&x0, &x);
        n++;
    }
    printf("\npi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");
    printf("n = %d\n", n);

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %d 時間 %d 分 %d 秒\n", (int)(tend - tstart) / 3600, (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%f秒\n", tend - tstart);
    return 0;
}