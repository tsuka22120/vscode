#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 100

struct NUMBER {
    int n[KETA];  // 各桁の変数
    int sign;     // 符号変数 -1: 負, 0: 0, 1: 正
};

void clearByZero(struct NUMBER *a) {
    int i;
    for (i = 0; i < KETA; i++) {
        a->n[i] = 0;
    }
    a->sign = 0;
}

void dispNumber(const struct NUMBER *a) {
    int i;
    if (a->sign == -1) {
        printf("- ");
    } else {
        printf("+ ");
    }
    for (i = KETA - 1; i >= 0; i--) {
        printf("%2d", a->n[i]);
    }
}

void dispNumberZeroSuppress(const struct NUMBER *a) {
    int i;
    if (a->sign == -1) {
        printf("-");
    } else if (a->sign == 0) {
        printf("+ 0");
        return;
    } else {
        printf("+");
    }
    for (i = KETA - 1; i >= 0; i--) {
        if (a->n[i] > 0) {
            break;
        }
    }
    for (; i >= 0; i--) {
        printf("%2d", a->n[i]);
    }
}

void setRnd(struct NUMBER *a, int k){
    if(k > KETA){
        printf("ERROR\n");
        return;
    }
    int i;
    for(i = 0; i < k; i++){
        a->n[i] = random() % 10;
    }
    for(i = k; i >= 0; i--){
        if(a->n[i] != 0){
            break;
        }
        if(i == 0){
            a->sign = 0;
            return;
        }
    }
    if(random() % 2 == 0){
        a->sign = 1;
    }else{
        a->sign = -1;
    }
}

int main(void) {
    srandom(time(NULL));
    struct NUMBER b;
    clearByZero(&b);
    for(int i = 0; i < 10; i++){
        setRnd(&b, 10000);
        dispNumberZeroSuppress(&b);
        printf("\n");
    }
    return 0;
}