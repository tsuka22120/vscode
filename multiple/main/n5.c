// 名無しの公式を使って円周率を求めるプログラム

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
    Number constant;  // 定数
    Number tmp1,tmp2;
    int numA;
    int numB;
    int n;
    setInt(&constant, 2);
    mulBy10SomeTimes(&constant, &constant, DIGIT + MARGIN);
    clearByZero(&x);
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&tmp1);
    n = 0;
    while (1) {
        printf("\r円周率計算%d回試行中", n);
        fflush(stdout);
        // 2nを求める
        numA = 2 * n - 1;                       // 分子
        numB = 2 * n;                           // 分母
        if(numA == -1){
            setInt(&a, 1);
        }else{
            setInt(&tmp1,&numA);
            fastMultiple(&a,&tmp1,&tmp1);
        }
        if(numB == 0){
            setInt(&b,1);
        }else{
            setInt(&tmp2,)
        }

    }
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