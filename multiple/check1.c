#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    time_t st, et;
    st = time(NULL);
    init_genrand((unsigned long)time(NULL));

    struct NUMBER a, b, c;
    int numA, numB, numC;
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    for (int i = 0; i < 100; i++) {
        numA = genrand_int32() % 1000;
        numB = genrand_int32() % 1000;
        setInt(&a, numA);
        setInt(&b, numB);
        if (multiple(&a, &b, &c) == -1) {
            printf("overflow\n");
            break;
        }
        getInt(&c, &numC);
        if (numA * numB != numC) {
            printf("error\n");
            break;
        }
    }

    et = time(NULL);
    printf("time: %ld\n", et - st);
    return 0;
}