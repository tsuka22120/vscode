// sharpの公式により円周率を求める

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "../pi.h"

int main(int argc, char **argv) {
    printf("%dLengthpi\n", DIGIT);
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    Number digitNum;  // 求める桁数
    Number constant;  // 定数
    Number x;         // 答え
    Number tmp;       // 作業用多倍長整数
    Number a, b;      // 項a,b
    Number three;
    int n;
    int numA = 0;
    n = 0;
    setInt(&constant, 6);
    setInt(&three, 3);
    setInt(&b, 1);
    // ルート3を求める
    sqrtThree(&digitNum);
    printf("root3 = ");
    dispNumber(&digitNum);
    printf("\n");
    printf("root3Len = %d\n", getLen(&digitNum));
    compareRootThree(&digitNum);
    // 6ルート3を求める
    multiple(&digitNum, &constant, &constant);
    // 初期値
    clearByZero(&x);
    n = 0;
    while (1) {
        printf("\r%d times", n);
        fflush(stdout);
        // aを求める
        numA = 2 * n + 1;
        setInt(&a, numA);
        // bを求める
        multiple(&b, &three, &b);
        // a * bを求める
        if (multiple(&a, &b, &tmp) == FALSE) {
            printf("overflow\n");
            break;
        }
        // xを求める
        if (divideByInverse(&constant, &tmp, &tmp) == FALSE) {
            printf("overflow\n");
            break;
        }
        if (isZero(&tmp)) {
            break;
        }
        if (n % 2 == 0) {
            if (add(&x, &tmp, &x) == FALSE) {
                printf("overflow\n");
                break;
            }
        } else {
            if (sub(&x, &tmp, &x) == FALSE) {
                printf("overflow\n");
                break;
            }
        }
        n++;
    }
    printf("\n");
    divBy10SomeTimes(&x, &x, MARGIN);
    printf("pi = ");
    dispNumber(&x);
    printf("\n");
    printf("piLen = %d\n", getLen(&x));
    comparePi(&x);

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("time: %d h %d m %d s\n", (int)(tend - tstart) / 3600,
           (int)(tend - tstart) % 3600 / 60, (int)(tend - tstart) % 60);
    printf("%fs\n", tend - tstart);
    return 0;
}