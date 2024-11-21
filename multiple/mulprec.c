#include "mulprec.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "mt19937ar.c"

/// @brief 構造体の中身を0で初期化する
/// @param a 初期化する構造体
void clearByZero(struct NUMBER *a) {
    int i;
    for (i = 0; i < KETA; i++) {
        a->n[i] = 0;
    }
    setSign(a, 0);
}

/// @brief 数値を表示する
/// @param a 表示する構造体
void dispNumber(const struct NUMBER *a) {
    int i;
    if (getSign(a) == -1) {
        printf("-");
    } else {
        printf("+");
    }
    for (i = KETA - 1; i >= 0; i--) {
        printf("%2d", a->n[i]);
    }
}

/// @brief 先頭の0を抜いて表示する
/// @param a 表示する構造体
void dispNumberZeroSuppress(const struct NUMBER *a) {
    int i;
    if (getSign(a) == -1) {
        printf("-");
    } else if (getSign(a) == 0) {
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
    clearByZero(a);
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
            setSign(a, 0);
            return;
        }
    }
    if (genrand_int32() % 2 == 0) {
        setSign(a, 1);
    } else {
        setSign(a, -1);
    }
}

/// @brief 値をコピーする
/// @param a コピー先
/// @param b コピー元
void copyNumber(struct NUMBER *a, const struct NUMBER *b) {
    clearByZero(a);
    for (int i = 0; i < KETA; i++) {
        a->n[i] = b->n[i];
    }
    setSign(a, getSign(b));
}

/// @brief 絶対値を求める
/// @param a 絶対値を求める構造体
/// @param b 絶対値を代入する構造体
void getAbs(const struct NUMBER *a, struct NUMBER *b) {
    copyNumber(b, a);
    if (getSign(a) == 0) {
        setSign(b, 0);
    } else {
        setSign(b, 1);
    }
}

/// @brief aが0かどうかを判定する
/// @param a 判定する構造体
/// @return 0: 0でない, -1: 0
int isZero(const struct NUMBER *a) {
    if (getSign(a) == 0) {
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
    setSign(b, getSign(a));
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
    setSign(b, getSign(a));
    rtn = a->n[0];
    return rtn;
}

/// @brief int型の値を構造体に代入する
/// @param a 代入する構造体
/// @param x 代入する値
/// @return 成功: 0, エラー(overflow): -1
int setInt(struct NUMBER *a, int x) {
    clearByZero(a);
    int i;
    int r;
    if (x < 0) {
        setSign(a, -1);
        x *= -1;
    } else if (x == 0) {
        setSign(a, 0);
    } else {
        setSign(a, 1);
    }
    for (i = 0; i < KETA; i++) {
        r = x % 10;
        a->n[i] = r;
        x -= r;
        x /= 10;
        if (x == 0) {
            break;
        }
    }
    if (x != 0) {
        return -1;
    }
    return 0;
}

/// @brief 構造体の中身をint型に変換する
/// @param a 値を読み取る構造体
/// @param x int型に変換した値を代入する変数
/// @return 成功: 0, エラー(overflow): -1
int getInt(const struct NUMBER *a, int *x) {
    if (getSign(a) == 0) {
        *x = 0;
        return 0;
    }
    int i;
    int MAX = INT_MAX;
    int MIN = INT_MIN;
    int MAXlen = 0, MINlen = 0;
    int MAXdigit[KETA], MINdigit[KETA];
    // int型の最大値と最小値の桁数とそれぞれの桁の値を求める
    i = 0;
    while (MAX != 0) {
        MAXdigit[i] = MAX % 10;
        MAX -= MAXdigit[i];
        MAX /= 10;
        MAXlen++;
        i++;
    }
    i = 0;
    while (MIN != 0) {
        MINdigit[i] = MIN % 10;
        MIN -= MINdigit[i];
        MIN /= 10;
        MINlen++;
        i++;
    }
    // 多倍長の桁数がint型の最大値と最小値の桁数より大きい場合はエラー
    for (i = 0; i < KETA - MAXlen; i++) {
        if (getSign(a) == -1) {
            if (a->n[MAXlen + i] != 0) {
                return -1;
            }
        } else {
            if (a->n[MINlen + i] != 0) {
                return -1;
            }
        }
    }
    // 多倍長とint型の各桁を比較
    if (getSign(a) == 1) {
        for (i = 0; i < MAXlen; i++) {
            if (a->n[MAXlen - 1 - i] > MAXdigit[MAXlen - 1 - i]) {
                return -1;
            } else if (a->n[MAXlen - 1 - i] < MAXdigit[MAXlen - 1 - i]) {
                break;
            }
        }
    } else {
        for (i = 0; i < MINlen; i++) {
            if (a->n[MINlen - 1 - i] < MINdigit[MINlen - 1 - i]) {
                return -1;
            } else if (a->n[MINlen - 1 - i] > MINdigit[MINlen - 1 - i]) {
                break;
            }
        }
    }
    *x = 0;
    for (i = KETA - 1; i >= 0; i--) {
        *x *= 10;
        *x += a->n[i];
    }
    if (getSign(a) == -1) {
        *x *= -1;
    }
    return 0;
}

/// @brief 符号を設定する
/// @param a 符号を設定する構造体
/// @param s 1: 正, 0: 0, -1: 負
/// @return 成功: 0, エラー: -1
int setSign(struct NUMBER *a, int s) {
    if (s == 0) {
        a->sign = 0;
    } else if (s == 1) {
        a->sign = 1;
    } else if (s == -1) {
        a->sign = -1;
    } else {
        return -1;
    }
    return 0;
}

/// @brief 符号を取得する
/// @param a 符号を取得する構造体
/// @return 1: 正, 0: 0, -1: 負
int getSign(const struct NUMBER *a) { return a->sign; }

/// @brief 2つの多倍長整数を比較する
/// @param a 比較する構造体
/// @param b 比較する構造体
/// @return 1: a > b, 0: a = b, -1: a < b
int numComp(const struct NUMBER *a, const struct NUMBER *b) {
    int i;
    if (getSign(a) > getSign(b)) {
        return 1;
    } else if (getSign(a) < getSign(b)) {
        return -1;
    }
    if (getSign(a) == getSign(b) && getSign(a) == 0) {
        return 0;
    }
    if(getSign(a) == getSign(b) && getSign(a) == 1){
        for (i = KETA - 1; i >= 0; i--) {
            if (a->n[i] > b->n[i]) {
                return 1;
            } else if (a->n[i] < b->n[i]) {
                return -1;
            }
        }
        return 0;
    }else if(getSign(a) == getSign(b) && getSign(a) == -1){
        for (i = KETA - 1; i >= 0; i--) {
            if (a->n[i] < b->n[i]) {
                return 1;
            } else if (a->n[i] > b->n[i]) {
                return -1;
            }
        }
        return 0;
    }
    return 0;
}

/// @brief 2つの多倍長整数を入れ替える
/// @param a 入れ替える構造体
/// @param b 入れ替える構造体
void swap(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER tmp;
    copyNumber(&tmp, a);
    copyNumber(a, b);
    copyNumber(b, &tmp);
}