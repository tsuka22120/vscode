#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "mt19937ar.h"
#include "mulprec.h"

int main(int argc, char **argv) {
    time_t st, et;
    st = time(NULL);
    init_genrand((unsigned long)time(NULL));

    struct NUMBER a, b;
    setInt(&a, -999);
    if(decrement(&a, &b) == -1) {
        printf("overflow\n");
    }

    et = time(NULL);
    printf("time: %ld\n", et - st);
    return 0;
}