#include "pi.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief 符号を設定する
/// @param a 符号を設定する構造体
/// @param s 1: 正, 0: 0, -1: 負
/// @return 成功: 0, エラー: -1
int setSign(Number *a, int s) {
    switch (s) {
        case PLUS:
            a->sign = PLUS;
            break;
        case ZERO:
            a->sign = ZERO;
            break;
        case MINUS:
            a->sign = MINUS;
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

/// @brief 符号を取得する
/// @param a 符号を取得する構造体
/// @return 1: 正, 0: 0, -1: 負
int getSign(const Number *a) { return a->sign; }

/// @brief 構造体の中身を0で初期化する
/// @param a 初期化する構造体
void clearByZero(Number *a) {
    for (int i = 0; i < KETA; i++) {
        a->n[i] = 0;
    }
    setSign(a, ZERO);
}

/// @brief 先頭の0を抜いて表示する
/// @param a 表示する構造体
void dispNumber(const Number *a) {
    int i;
    char format[8];
    sprintf(format, " %%0%dd", RADIX_LEN);  // format = " %02d"
    switch (getSign(a)) {
        case PLUS:
            printf("+");
            break;
        case ZERO:
            printf("+ 0");
            return;
        case MINUS:
            printf("-");
            break;
    }
    for (i = KETA - 1; i >= 0; i--) {
        if (a->n[i] > 0) {
            break;
        }
    }
    for (; i >= 0; i--) {
        printf(format, a->n[i]);
    }
}

/// @brief 値をコピーする
/// @param a コピー先
/// @param b コピー元
void copyNumber(Number *a, const Number *b) { *a = *b; }

/// @brief 絶対値を求める
/// @param a 絶対値を求める構造体
/// @param b 絶対値を代入する構造体
void getAbs(const Number *a, Number *b) {
    copyNumber(b, a);
    if (getSign(a) == ZERO) {
        setSign(b, ZERO);
    } else {
        setSign(b, PLUS);
    }
}

/// @brief aが0かどうかを判定する
/// @param a 判定する構造体
/// @return true: 0, false: 0でない
int isZero(const Number *a) {
    if (getSign(a) == ZERO) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/// @brief aを何回か10倍してbに代入する
/// @param a 10倍する構造体
/// @param b 10倍した値を代入する構造体
/// @param k 10倍する回数
/// @return 0: 正常終了, -1: オーバーフロー
int mulBy10SomeTimes(const Number *a, Number *b, int k) {
    int rtn = -2;
    int i, j;
    copyNumber(b, a);
    if (isZero(a)) {
        rtn = TRUE;
    } else if (k == 0) {
        rtn = TRUE;
    } else {
        int digit;
        RADIX_T carry;
        digit = k / RADIX_LEN;
        int length = getLen(b);
        j = 0;
        i = KETA - 1;
        while (1) {
            if (digit <= j) {
                break;
            } else if (b->n[i] != 0) {
                printf("mulBy10SomeTimes: overflow: -1A\n");
                rtn = FALSE;
                break;
            }
            j++;
            i--;
        }
        if (rtn == FALSE) {
            printf("mulBy10SomeTimes: overflow: -1B\n");
        } else if (b->n[i] /
                       (int)pow(10, (RADIX_LEN - (k % RADIX_LEN))) !=
                   0) {
            printf("mulBy10SomeTimes: overflow\n");
            rtn = FALSE;
        } else {
            if (digit != 0) {
                for (i = length / RADIX_LEN; i >= 0; i--) {
                    b->n[i + digit] = b->n[i];
                }
                for (i = 0; i < digit; i++) {
                    b->n[i] = 0;
                }
            }
            length += digit * RADIX_LEN;
            carry = 0;
            for (i = 0; i < length / RADIX_LEN + 2; i++) {
                b->n[i] *= (int)pow(10, (k % RADIX_LEN));
                b->n[i] += carry;
                if (b->n[i] >= RADIX) {
                    carry = b->n[i] / RADIX;
                    b->n[i] %= RADIX;
                } else {
                    carry = 0;
                }
            }
            rtn = TRUE;
        }
    }
    return rtn;
}

/// @brief aを何回か10で割ってbに代入する
/// @param a 10で割る構造体
/// @param b 10で割った値を代入する構造体
/// @param k 10で割る回数
/// @return 剰余
void divBy10SomeTimes(const Number *a, Number *b, int k) {
    int i;
    int digit;
    int carry;
    digit = k / RADIX_LEN;
    copyNumber(b, a);
    b->n[0] -= b->n[0] % (int)pow(10, k % RADIX_LEN);
    b->n[0] /= (int)pow(10, k % RADIX_LEN);
    for (i = 1; i < KETA; i++) {
        carry = b->n[i] % (int)pow(10, k % RADIX_LEN);
        b->n[i - 1] +=
            carry * (int)pow(10, RADIX_LEN - (k % RADIX_LEN));
        b->n[i] -= carry;
        b->n[i] /= (int)pow(10, k % RADIX_LEN);
    }
    if (digit > 0) {
        for (i = 0; i < KETA - digit; i++) {
            b->n[i] = b->n[i + digit];
        }
        for (i = KETA - digit; i < KETA; i++) {
            b->n[i] = 0;
        }
    }
    return;
}

/// @brief int型の値を構造体に代入する
/// @param a 代入する構造体
/// @param x 代入する値
/// @return 成功: 0, エラー(overflow): -1
int setInt(Number *a, long x) {
    clearByZero(a);
    if (x < 0) {
        setSign(a, MINUS);
        x *= -1;
    } else if (x == 0) {
        setSign(a, ZERO);
    } else {
        setSign(a, PLUS);
    }
    a->n[0] = x % RADIX;
    return TRUE;
}

/// @brief 構造体の中身をint型に変換する
/// @param a 値を読み取る構造体
/// @param x int型に変換した値を代入する変数
/// @return 成功: 0, エラー(overflow): -1
int getInt(const Number *a, int *x) {
    int rtn;
    if (isZero(a)) {
        *x = 0;
        rtn = TRUE;
    } else if (getLen(a) > RADIX_LEN) {
        rtn = FALSE;
    } else {
        *x = a->n[0];
        *x += a->n[1] * RADIX;
        if (getSign(a) == MINUS) {
            *x *= -1;
        }
        rtn = TRUE;
    }
    return rtn;
}

/// @brief 2つの多倍長整数を比較する
/// @param a 比較する構造体
/// @param b 比較する構造体
/// @return 1: a > b, 0: a = b, -1: a < b
int numComp(const Number *a, const Number *b) {
    int rtn = 0;
    switch (getSign(a) * 3 + getSign(b)) {
        case -4:  // aとbが負
            if (getLen(a) > getLen(b)) {
                rtn = -1;
            } else if (getLen(a) < getLen(b)) {
                rtn = 1;
            }
            for (int i = KETA - 1; i >= 0; i--) {
                if (a->n[i] < b->n[i]) {
                    rtn = 1;
                    break;
                } else if (a->n[i] > b->n[i]) {
                    rtn = -1;
                    break;
                }
            }
            break;
        case 4:  // aとbが正
            if (getLen(a) > getLen(b)) {
                rtn = 1;
            } else if (getLen(a) < getLen(b)) {
                rtn = -1;
            }
            for (int i = KETA - 1; i >= 0; i--) {
                if (a->n[i] > b->n[i]) {
                    rtn = 1;
                    break;
                } else if (a->n[i] < b->n[i]) {
                    rtn = -1;
                    break;
                }
            }
            break;
        case -3:  // aが負でbが0
        case -2:  // aが負でbが正
        case 1:   // aが0でbが正
            rtn = -1;
            break;
        case -1:  // aが0でbが負
        case 2:   // aが正でbが負
        case 3:   // aが正でbが0
            rtn = 1;
            break;
        case 0:  // aとbが0
            break;
    }
    return rtn;
}

/// @brief 多倍長整数とint型の値を比較する
/// @param a 比較する構造体
/// @param x 比較する値
/// @return 1: a > x, 0: a = x, -1: a < x
int numCompWithInt(const Number *a, int x) {
    int num, rtn;
    if (getInt(a, &num) == FALSE) {
        rtn = 1;
    } else if (num > x) {
        rtn = 1;
    } else if (num < x) {
        rtn = -1;
    } else {
        rtn = 0;
    }
    return rtn;
}

/// @brief 2つの多倍長整数を加算する(同じ変数を関数内に入れてはいけない)
/// @param a 加算する構造体
/// @param b 加算する構造体
/// @param c 加算した値を代入する構造体
/// @return オーバーフロー: -1, 正常終了: 0
int add(const Number *a, const Number *b, Number *c) {
    Number A, B;
    RADIX_T d;
    int i, rtn;
    int e = 0;
    rtn = -2;
    int caseNum = getSign(a) * 3 + getSign(b);
    switch (caseNum) {
        case -4:  // aとbが負
        case 4:   // aとbが正
            // clearByZero(c);
            if (caseNum == -4) {
                getAbs(a, &A);
                getAbs(b, &B);
                setSign(c, MINUS);
            } else {
                copyNumber(&A, a);
                copyNumber(&B, b);
                setSign(c, PLUS);
            }
            for (i = 0; i < KETA; i++) {
                d = A.n[i] + B.n[i] + e;
                e = 0;
                if (d >= RADIX) {
                    d -= RADIX;
                    e = 1;
                } else {
                    e = 0;
                }
                c->n[i] = d;
            }
            if (e == 1) {
                rtn = FALSE;
            } else {
                rtn = TRUE;
            }
            break;
        case -3:  // aが負でbが0
        case 3:   // aが正でbが0
            copyNumber(c, a);
            rtn = TRUE;
            break;
        case -2:  // aが負でbが正
            getAbs(a, &A);
            rtn = sub(b, &A, c);
            break;
        case -1:  // aが0でbが負
        case 1:   // aが0でbが正
            copyNumber(c, b);
            rtn = TRUE;
            break;
        case 0:  // aとbが0
            clearByZero(c);
            rtn = TRUE;
            break;
        case 2:  // aが正でbが負
            getAbs(b, &B);
            rtn = sub(a, &B, c);
            break;
    }
    return rtn;
}

/// @brief 2つの多倍長整数を減算する(同じ変数を関数内に入れてはいけない)
/// @param a 減算する構造体
/// @param b 減算する構造体
/// @param c 減算した値を代入する構造体
/// @return オーバーフロー: -1, 正常終了: 0
int sub(const Number *a, const Number *b, Number *c) {
    Number A, B;
    copyNumber(&A, a);
    copyNumber(&B, b);
    int i, e, num, rtn;
    int caseNum = getSign(&A) * 3 + getSign(&B);
    Number numA, numB;
    rtn = -2;
    switch (caseNum) {
        case -4:  // aとbが負
        case 4:   // aとbが正
            if (caseNum == -4) {
                getAbs(&A, &numB);
                getAbs(&B, &numA);
            } else {
                copyNumber(&numA, &A);
                copyNumber(&numB, &B);
            }
            e = 0;
            switch (numComp(&A, &B)) {
                case 1:
                    for (i = 0; i < KETA; i++) {
                        num = numA.n[i] - e;
                        if (num < numB.n[i]) {
                            c->n[i] = num + RADIX - numB.n[i];
                            e = 1;
                        } else {
                            c->n[i] = num - numB.n[i];
                            e = 0;
                        }
                        setSign(c, PLUS);
                    }
                    break;
                case -1:
                    for (i = 0; i < KETA; i++) {
                        num = numB.n[i] - e;
                        if (num < numA.n[i]) {
                            c->n[i] = num + RADIX - numA.n[i];
                            e = 1;
                        } else {
                            c->n[i] = num - numA.n[i];
                            e = 0;
                        }
                    }
                    setSign(c, MINUS);
                    break;
                case 0:
                    clearByZero(c);
                    setSign(c, ZERO);
                    break;
            }
            if (e > 0) {
                rtn = FALSE;
            } else {
                rtn = TRUE;
            }
            break;
        case -3:  // aが負でbが0
        case 3:   // aが正でbが0
            copyNumber(c, &A);
            rtn = TRUE;
            break;
        case -2:  // aが負でbが正
            getAbs(&A, &A);
            rtn = add(&A, &B, c);
            setSign(c, MINUS);
            break;
        case -1:  // aが0でbが負
            copyNumber(c, &B);
            setSign(c, PLUS);
            rtn = TRUE;
            break;
        case 1:  // aが0でbが正
            copyNumber(c, &B);
            setSign(c, MINUS);
            rtn = TRUE;
            break;
        case 0:  // aとbが0
            clearByZero(c);
            rtn = TRUE;
            break;
        case 2:  // aが正でbが負
            getAbs(&B, &B);
            rtn = add(&A, &B, c);
            break;
    }
    return rtn;
}

/// @brief 2つの多倍長整数を掛け算する
/// @param a 掛け算する構造体
/// @param b 掛け算する構造体
/// @param c 掛け算した値を代入する構造体
/// @return オーバーフロー: -1, 正常終了: 0
int multiple(const Number *a, const Number *b, Number *c) {
    int rtn = -2;
    int signA, signB;
    signA = getSign(a);
    signB = getSign(b);
    if (signA == ZERO || signB == ZERO) {
        clearByZero(c);
        rtn = TRUE;
    } else {
        RADIX_T tmp;
        Number A, B;
        getAbs(a, &A);
        getAbs(b, &B);
        clearByZero(c);
        int ALength = getLen(&A);
        int BLength = getLen(&B);
        for (int i = 0; i < ALength / 9 + 1; i++) {
            for (int j = 0; j < BLength / 9 + 1; j++) {
                tmp = A.n[i] * B.n[j];
                if (tmp == 0) {
                    continue;
                }
                c->n[i + j] += tmp % RADIX;
                c->n[i + j + 1] += tmp / RADIX;
                c->n[i + j + 1] += c->n[i + j] / RADIX;
                c->n[i + j] %= RADIX;
            }
        }
        switch (signA * 3 + signB) {
            case -4:  // aとbが負
            case 4:   // aとbが正
                setSign(c, PLUS);
                break;
            case -2:  // aが負でbが正
            case 2:   // aが正でbが負
                setSign(c, MINUS);
                break;
                // case 3:,case 1:,case 0:,case -1:,case
                // -3:は最初で判定しているのでここには来ない
        }
        rtn = TRUE;
    }
    return rtn;
}

/// @brief 多倍長整数の逆数を求める(3次収束)
/// @param a 逆数を求める構造体
/// @param b 逆数を代入する構造体
/// @return ゼロ除算: -1, 正常終了: 余裕を持っている桁数
int inverse3(const Number *a, Number *b) {
    int rtn = TRUE;
    if (isZero(a)) {
        clearByZero(b);
        rtn = TRUE;
    } else if (numCompWithInt(a, 1) == 0) {
        copyNumber(b, a);
        mulBy10SomeTimes(b, b, DIGIT + MARGIN);
        rtn = TRUE;
    } else {
        Number x0;   //  ひとつ前のx
        Number A;    //  逆数を求める数
        Number tmp;  // 作業用変数
        Number h;
        Number g;  // 逆数の誤差
        Number bigOne;
        int sigDigs = DIGIT + MARGIN;
        int margin = 0;
        int length = getLen(a);
        if(length >= sigDigs + margin) {
            margin += length;
        } else {
            margin += sigDigs;
        }
        getAbs(a, &A);
        setInt(&bigOne, 1);
        setInt(b, 2);
        mulBy10SomeTimes(b, b, sigDigs + margin - length);  // 初期値
        mulBy10SomeTimes(&bigOne, &bigOne, sigDigs + margin);
        while (1) {
            copyNumber(&x0, b);  //  ひとつ前のx
            if (multiple(&A, &x0, &tmp) == -1) {
                printf("ERROR:inverse2 overflow\n");
                clearByZero(b);
                rtn = FALSE;
                break;
            }
            sub(&bigOne, &tmp, &h);
            multiple(&h, &h, &tmp);
            divBy10SomeTimes(&tmp, &tmp, sigDigs + margin);
            add(&tmp, &h, &tmp);
            add(&tmp, &bigOne, &tmp);
            if (multiple(&x0, &tmp, b) == -1) {
                printf("ERROR:inverse2 overflow\n");
                clearByZero(b);
                rtn = FALSE;
                break;
            }
            divBy10SomeTimes(b, b, sigDigs + margin);
            sub(b, &x0, &g);
            if (getLen(&g) < 2) {
                rtn = margin;
                break;
            }
        }
        setSign(b, getSign(a));
    }
    return rtn;
}

/// @brief 多倍長整数を割り算する(逆数使用)
/// @param a 被除数
/// @param b 除数
/// @param c 商を代入する構造体
/// @return ゼロ除算: -1, 正常終了: 0
int divideByInverse(const Number *a, const Number *b, Number *c) {
    Number A, B;
    getAbs(a, &A);
    getAbs(b, &B);
    if (numComp(&A, &B) == -1) {
        clearByZero(c);
        return 0;
    }
    int rtn;
    int cSign;
    Number inv;
    int margin = 0;
    switch ((getSign(a) < 0) * 2 + (getSign(b) < 0)) {
        case 0:  // Aが正でBが正
        case 3:  // Aが負でBが負
            cSign = 1;
            break;
        case 1:  // Aが正でBが負
        case 2:  // Aが負でBが正
            cSign = -1;
            break;
    }
    margin = inverse3(&B, &inv);
    if (margin == FALSE) {
        printf("ERROR:divideByInverse errorA\n");
        rtn = FALSE;
    } else {
        if (multiple(&A, &inv, c) == -1) {
            printf("ERROR:divideByInverse errorB\n");
            rtn = FALSE;
        } else {
            divBy10SomeTimes(c, c, DIGIT + MARGIN + margin);
            rtn = TRUE;
        }
    }
    setSign(c, cSign);
    return rtn;
}

/// @brief 3の平方根を求める
/// @param a 3の平方根を代入する構造体
/// @return エラー: -1, 正常終了: 0
int sqrtThree(Number *a) {
    clearByZero(a);
    int rtn;
    Number numA, numB;
    Number constant;
    Number numA0, numB0;
    Number two;
    int digSig = DIGIT + MARGIN;
    int i;
    int j = 0;
    i = 1;
    // digSigが2の何乗かを求める
    while (1) {
        if (digSig < i) {
            break;
        }
        i *= 2;
        j++;
    }

    setInt(&constant, 3);
    setInt(&two, 2);
    setInt(&numA, 1);
    copyNumber(&numB, &numA);
    for (i = 0; i < j + 1; i++) {
        printf("\rroot3 calculate %d", i);
        fflush(stdout);
        copyNumber(&numA0, &numA);
        copyNumber(&numB0, &numB);
        if (multiple(&numA0, &numA0, &numA) == FALSE) {
            printf("ERROR:sqrtThree overflowA\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        if (multiple(&numB0, &numB0, &numB) == FALSE) {
            printf("ERROR:sqrtThree overflowB\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        if (multiple(&numB, &constant, &numB) == FALSE) {
            printf("ERROR:sqrtThree overflowC\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        if (add(&numA, &numB, &numA) == FALSE) {
            printf("ERROR:sqrtThree overflowD\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        if (multiple(&numA0, &numB0, &numB) == FALSE) {
            printf("ERROR:sqrtThree overflowE\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        if (multiple(&numB, &two, &numB) == FALSE) {
            printf("ERROR:sqrtThree overflowF\n");
            clearByZero(a);
            rtn = FALSE;
            break;
        }
        rtn = TRUE;
    }
    printf("\n");
    if (rtn != FALSE) {
        if (mulBy10SomeTimes(&numA, &numA, DIGIT + MARGIN) == FALSE) {
            printf("ERROR:sqrtThree overflowG\n");
            clearByZero(a);
            rtn = FALSE;
        } else if (divideByInverse(&numA, &numB, a) == FALSE) {
            printf("ERROR:sqrtThree overflowH\n");
            clearByZero(a);
            rtn = FALSE;
        }
    }
    return rtn;
}

/// @brief 多倍長整数の桁数を求める
/// @param a 桁数を求める構造体
/// @return 桁数
int getLen(const Number *a) {
    int i;
    if (isZero(a)) {
        return 1;
    }
    for (i = KETA - 1; i >= 0; i--) {
        if (a->n[i] != 0) {
            break;
        }
    }
    return i * RADIX_LEN + (int)log10(a->n[i]) + 1;
}

/// @brief 多倍長整数がpiと等しいか判定する
/// @param a 判定する構造体
/// @return 等しい: 0, 等しくない: -1
int comparePi(const Number *a) {
    FILE *fp;
    int num;
    int length;
    char format[10];
    length = getLen(a);
    fp = fopen("./text/pi.txt", "r");
    for (int i = 0; i < length % 9; i++) {
        format[i] = fgetc(fp);
    }
    num = atoi(format);
    if (a->n[length / 9] != num) {
        printf("一致しません\n");
        printf("a->n[%d]: %lld, num: %d\n", length / 9, a->n[length / 9], num);
        fclose(fp);
        return FALSE;
    }
    // 9桁ずつ比較する
    for (int i = length / 9 - 1; i >= 0; i--) {
        if (fgets(format, 10, fp) == NULL) {
            printf("fgets error\n");
            fclose(fp);
            return FALSE;
        }
        num = atoi(format);
        if (a->n[i] != num) {
            printf("一致しません\n");
            printf("a->n[%d]: %lld, num: %d\n", i, a->n[i], num);
            fclose(fp);
            return FALSE;
        }
    }
    fclose(fp);
    printf("same\n");
    return 0;
}

/// @brief 多倍長整数がroot3と等しいか判定する
/// @param a 判定する構造体
/// @return 等しい: 0, 等しくない: -1
int compareRootThree(const Number *a) {
    FILE *fp;
    int num;
    int length;
    char format[10];
    length = getLen(a);
    fp = fopen("./text/root3.txt", "r");
    for (int i = 0; i < length % 9; i++) {
        format[i] = fgetc(fp);
    }
    num = atoi(format);
    if (a->n[length / 9] != num) {
        printf("一致しません\n");
        printf("a->n[%d]: %lld, num: %d\n", length / 9, a->n[length / 9], num);
        fclose(fp);
        return FALSE;
    }
    // 9桁ずつ比較する
    for (int i = length / 9 - 1; i >= 0; i--) {
        if (fgets(format, 10, fp) == NULL) {
            fclose(fp);
            printf("fgets error\n");
            return FALSE;
        }
        num = atoi(format);
        if (a->n[i] != num) {
            printf("一致しません\n");
            printf("a->n[%d]: %lld, num: %d\n", i, a->n[i], num);
            fclose(fp);
            return FALSE;
        }
    }
    fclose(fp);
    printf("same\n");
    return 0;
}