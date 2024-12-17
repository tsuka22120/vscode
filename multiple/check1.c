#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    time_t st, et;
    st = time(NULL);
    init_genrand((unsigned long)time(NULL));

    // struct NUMBER a, b,c;
    // setInt(&a, -70);
    // setInt(&b, 31);
    // printf("a: ");
    // dispNumberZeroSuppress(&a);
    // printf("\n");
    // printf("b: ");
    // dispNumberZeroSuppress(&b);
    // printf("\n");
    // multiple(&a, &b, &c);
    // printf("c: ");
    // dispNumberZeroSuppress(&c);
    // printf("\n");

    struct NUMBER a, b, c;
    int numA, numB, numC;
    for (int i = 0; i < 1000; i++) {
        numA = genrand_int32() % 10000 * -1;
        numB = genrand_int32() % 10000;

        setInt(&a, numA);
        setInt(&b, numB);
        multiple(&a, &b, &c);
        getInt(&c, &numC);
        if(numA * numB != numC) {
            printf("numA: %d, numB: %d, numC: %d\n", numA, numB, numC);
            printf("error\n");
            break;
        }
    }

    et = time(NULL);
    printf("time: %ld\n", et - st);
    return 0;
}