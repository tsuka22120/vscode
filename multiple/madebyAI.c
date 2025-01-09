#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 1000  // 円周率の桁数
#define BASE 10      // 基数（10進数）

// 多倍長計算用の整数配列加算
void addArrays(int *result, int *term, int precision) {
    for (int i = 0; i < precision; i++) {
        result[i] += term[i];
        if (result[i] >= BASE) {
            result[i] -= BASE;
            result[i + 1]++;
        }
    }
}

// 多倍長計算用の整数配列減算
void subtractArrays(int *result, int *term, int precision) {
    for (int i = 0; i < precision; i++) {
        result[i] -= term[i];
        if (result[i] < 0) {
            result[i] += BASE;
            result[i + 1]--;
        }
    }
}

// 逆数の計算（指定されたxに対する1/x）
void reciprocal(int *result, int x, int precision) {
    int *term = calloc(precision, sizeof(int));
    int *xPower = calloc(precision, sizeof(int));
    int *temp = calloc(precision, sizeof(int));

    if (term == NULL || xPower == NULL || temp == NULL) {
        fprintf(stderr, "Memory allocation failed in reciprocal function\n");
        exit(1);
    }

    term[0] = BASE / x;  // 1/x の初期項
    memcpy(xPower, term, precision * sizeof(int));

    for (int i = 1; term[0] != 0 || term[1] != 0; i++) {
        memcpy(temp, term, precision * sizeof(int));

        // x^2 を掛ける
        for (int j = 0; j < precision; j++) {
            term[j] = xPower[j] * xPower[j];
        }

        addArrays(result, term, precision);  // 結果を加算
    }

    free(term);
    free(xPower);
    free(temp);
}

// マチンの公式を使用して円周率を計算する
void calculatePi(int *result, int precision) {
    int *arctan1_5 = calloc(precision, sizeof(int));
    int *arctan1_239 = calloc(precision, sizeof(int));

    if (arctan1_5 == NULL || arctan1_239 == NULL) {
        fprintf(stderr, "Memory allocation failed in calculatePi function\n");
        exit(1);
    }

    reciprocal(arctan1_5, 5, precision);      // arctan(1/5)
    reciprocal(arctan1_239, 239, precision);  // arctan(1/239)

    memset(result, 0, precision * sizeof(int));
    for (int i = 0; i < precision; i++) {
        result[i] = 16 * arctan1_5[i] - 4 * arctan1_239[i];
    }

    free(arctan1_5);
    free(arctan1_239);
}

// 結果を表示する
void printPi(int *pi, int precision) {
    printf("3.");
    for (int i = 0; i < precision; i++) {
        printf("%d", pi[i]);
    }
    printf("\n");
}

int main() {
    int precision = DIGITS + 10;
    int *pi = calloc(precision, sizeof(int));

    if (pi == NULL) {
        fprintf(stderr, "Memory allocation failed in main function\n");
        return 1;
    }

    calculatePi(pi, precision);
    printPi(pi, DIGITS);

    free(pi);  // メモリ解放

    return 0;
}
