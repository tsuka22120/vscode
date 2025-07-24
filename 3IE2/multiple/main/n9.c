// オイラーの公式を用いて円周率を求めるプログラム

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "../mt19937ar.h"
#include "../mulprec2.h"

int main(int argc, char **argv) {
    printf("円周率を%d桁求めます。使用する多倍長整数の桁数:%d\n", DIGIT, KETA);
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    init_genrand((unsigned long)time(NULL));

    Number a, b;      // 項a,b
    Number x;         // 答え
    Number tmp1,tmp2;       // 作業用多倍長整数
    Number constant;  // 定数
    int i;
    setInt(&constant, 2);
    mulBy10SomeTimes(&constant, &constant, DIGIT + MARGIN);
    clearByZero(&x);
    i = 0;
    while (1) {
        printf("\r円周率計算%d回試行中", i);
        fflush(stdout);
        if (i == 0) {
            setInt(&a, 1);
        } else {
            setInt(&tmp1, i);
            fastMultiple(&a, &tmp1, &a);
        }
        fastMultiple(&a, &constant, &tmp1);
        if(i == 0){
            setInt(&b, 1);
        } else {
            setInt(&tmp2, 2 * i + 1);
            fastMultiple(&b, &tmp2, &b);
        }
        if(divideByInverse(&tmp1, &b, &tmp1) == -1) {  // a /= (2i + 1)!!
            printf("overflow\n");
            break;
        }
        if (isZero(&tmp1)) {
            break;
        }
        if(add(&x, &tmp1, &x) == -1) {  // x += a
            printf("overflow\n");
            break;
        }
        i++;
    }
    printf("\n");
    divBy10SomeTimes(&x, &x, MARGIN);
    printf("pi = ");
    dispNumberZeroSuppress(&x);
    printf("\n");
    printf("piLen = %d\n", getLen(&x));
    comparePi(&x);

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("所要時間: %d 時間 %d 分 %d 秒\n", (int)(tend - tstart) / 3600,
           (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%f秒\n", tend - tstart);
    return 0;
}