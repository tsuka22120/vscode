#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MT.h"

#define KETA 100

struct NUMBER {
    int n[KETA];  // 各桁の変数
    int sign;     // 符号変数 -1: 負, 0: 0, 1: 正
};

/// @brief 構造体の中身を0で初期化する
/// @param a 初期化する構造体
void clearByZero(struct NUMBER *a) {
    int i;
    for (i = 0; i < KETA; i++) {
        a->n[i] = 0;
    }
    a->sign = 0;
}

/// @brief 数値を表示する
/// @param a 表示する構造体
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

/// @brief 先頭の0を抜いて表示する
/// @param a 表示する構造体
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

/// @brief 乱数を生成して代入する
/// @param a 乱数を代入する構造体のポインタ
/// @param k 乱数の桁数
void setRnd(struct NUMBER *a, int k) {
    if (k > KETA) {
        printf("ERROR:random number overflow\n");
        return;
    }
    int i;
    for (i = 0; i < k; i++) {
        a->n[i] = genrand_int32() % 10;
    }
    for (i = k; i >= 0; i--) {
        if (a->n[i] != 0) {
            break;
        }
        if (i == 0) {
            a->sign = 0;
            return;
        }
    }
    if (genrand_int32() % 2 == 0) {
        a->sign = 1;
    } else {
        a->sign = -1;
    }
}

/// @brief 値をコピーする
/// @param a コピー先
/// @param b コピー元
void copyNumber(struct NUMBER *a, const struct NUMBER *b) {
    for (int i = 0; i < KETA; i++) {
        a->n[i] = b->n[i];
    }
    a->sign = b->sign;
}

/// @brief 絶対値を求める
/// @param a 絶対値を求める構造体
/// @param b 絶対値を代入する構造体
void getAbs(const struct NUMBER *a, struct NUMBER *b) {
    copyNumber(b, a);
    b->sign = 1;
}

/// @brief aが0かどうかを判定する
/// @param a 判定する構造体
/// @return 0: 0でない, -1: 0
int isZero(const struct NUMBER *a) {
    int i;
    if (a->sign == 0) {
        return 0;
    } else {
        return -1;
    }
}

/// @brief aを10倍してbに代入する
/// @param a 10倍する構造体
/// @param b 10倍した値を代入する構造体
/// @return 0: 正常終了, -1: オーバーフロー
int mulBy10(const struct NUMBER *a, struct NUMBER *b) {
    int i;
    if (a->n[KETA - 1] != 0) {
        printf("ERROR:overflow\n");
        return -1;
    }
    for (i = 0; i < KETA - 1; i++) {
        b->n[i + 1] = a->n[i];
    }
    b->n[0] = 0;
    b->sign = a->sign;
    return 0;
}

/// @brief aを10で割ってbに代入する
/// @param a 10で割る構造体
/// @param b 10で割った値を代入する構造体
/// @return 剰余
int divBy10(const struct NUMBER *a, struct NUMBER *b) {
    int i;
    int rtn;
    for (i = 0; i < KETA - 1; i++) {
        b->n[i] = a->n[i + 1];
    }
    b->n[KETA - 1] = 0;
    b->sign = a->sign;
    if (a->sign == -1) {
        rtn = a->n[0] - a->n[0] * 2;
    } else {
        rtn = a->n[0];
    }
    return rtn;
}

int main(void) {
    init_genrand((unsigned)time(NULL));
    int i;
    struct NUMBER b, c;
    clearByZero(&b);
    for (i = 0; i < 10; i++) {
        setRnd(&b, 10);
        printf("b = ");
        dispNumberZeroSuppress(&b);
        printf("\n");
    }
    return 0;
}