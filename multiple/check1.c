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
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    setInt(&a, 1234);
    setInt(&b, 568);
    if(multiple(&a, &b, &c) == -1) {
        printf("overflow\n");
    }
    dispNumber(&a);
    printf("\n");
    dispNumber(&b);
    printf("\n");
    dispNumber(&c);
    printf("\n");

    et = time(NULL);
    printf("time: %ld\n", et - st);
    return 0;
}