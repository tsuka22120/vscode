// 出席番号:22番
// 氏名:塚田 勇人
// 課題内容:0以上500未満の乱数50個を自作のクイックソートを
// 使ってソートする。またソートをする際、過程がわかるように出力する。
// また追加機能として比較回数を測る機能、交換回数を測る機能、
// 要素数が5以下の場合はバブルソートを行う機能、
// ピボットを選ぶ際、配列の最初と真ん中と最後の値を比較し、中央値をピボットとする機能を追加した。
// そのプログラムは_NORMAL_VERを定義することで実行できる。

// また正常動作しているものとは別に、クイックソートの過程は表示しないが、
// ボゴソート、選択ソート、ヒープソート、バブルソートに要素数5から13までの範囲でクイックソートから
// 切り替え、1万回試行して比較回数と交換回数の平均を求め、最も比較回数が少ないパターンと
// 最も交換回数が少ないパターンを表示する機能を持つプログラムを作成した。
// そのプログラムは_ADDING_VERを定義することで実行できる。

#define _NORMAL_VER

#ifdef _NORMAL_VER
#define SWAP(a, b) ((a != b) && (a += b, b = a - b, a -= b))

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int indexNum;

/// @brief クイックソートを行う関数
/// @param ary ソートする配列
void quicksort(int ary[]);

/// @brief パーティション分割を行う関数
/// @param ary 分割する配列
/// @param left 分割する配列の範囲の左端のインデックス
/// @param right 分割する配列の範囲の右端のインデックス
/// @param comparableNum 比較回数のポインタ
/// @param changeNum 交換回数のポインタ
void partitioning(int ary[], int left, int right, int* comparableNum,
                  int* changeNum);

/// @brief ピボットを選択する関数
/// @param ary ピボットを選択する配列
/// @param left ピボットを選択する配列の範囲の左端のインデックス
/// @param right ピボットを選択する配列の範囲の右端のインデックス
/// @param comparableNum 比較回数のポインタ
/// @return ピボットの値
int choicePivot(int ary[], int left, int right, int* comparableNum);

/// @brief バブルソートを行う関数
/// @param ary ソートする配列
/// @param left ソートする配列の範囲の左端のインデックス
/// @param right ソートする配列の範囲の右端のインデックス
/// @param comparableNum 比較回数のポインタ
/// @param changeNum 交換回数のポインタ
void bubblesort(int ary[], int left, int right, int* comparableNum,
                int* changeNum);

/// @brief ソートが正常に行われているか判定する関数
/// @param ary 判定する配列
/// @return 正常に行われていたらtrue, そうでなければfalse
bool checkSort(int ary[]);

/// @brief 配列を0以上500未満の乱数で生成する関数
/// @param ary 生成する配列
void makeRandomAry(int ary[]);

/// @brief 配列を表示する関数
/// @param ary 表示する配列
/// @param left 表示する配列の範囲の左端のインデックス
/// @param right 表示する配列の範囲の右端のインデックス
void showAry(int ary[], int left, int right);

int main(void) {
    int i;
    // 乱数の種を設定
    srand((unsigned int)time(NULL));
    int ary[100000];
    for (i = 0; i < 100000; i++) {
        indexNum = rand() % 99991 + 10;
        makeRandomAry(ary);
        quicksort(ary);
    }
    return 0;
}

void quicksort(int ary[]) {
    // printf("~~クイックソート開始~~\n\n");
    int left, right;  // ソートする配列の左端:left と右端:right
    int comparableNum = 0,
        changeNum = 0;  // comparableNum:比較回数 changeNum:交換回数
    // printf("ソート前:");
    showAry(ary, 0, indexNum - 1);
    // printf("\n");
    left = 0;
    right = indexNum - 1;
    partitioning(ary, left, right, &comparableNum, &changeNum);
    // printf("ソート後:");
    showAry(ary, 0, indexNum - 1);
    if (checkSort(ary) == false) {
        // printf("error\n");
        // printf("\n");
    } else {
        // printf("比較回数:%d\n", comparableNum);
        // printf("交換回数:%d\n", changeNum);
        // printf("クイックソート終了\n");
        printf("%d ", indexNum);
        printf("%d\n", comparableNum);
    }
}

void partitioning(int ary[], int left, int right, int* comparableNum,
                  int* changeNum) {
    if (right - left < 1) {
        return;
    }
    int pivot;
    int leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
    // 左右の端のインデックスを保存しておき、再帰呼び出しの際に使う
    // printf("パーティション分割前:");
    showAry(ary, left, right);
    // printf("\n");
    pivot = choicePivot(ary, left, right, comparableNum);
    while (1) {
        (*comparableNum)++;
        while (ary[left] < pivot) {
            left++;
            (*comparableNum)++;
        }
        (*comparableNum)++;
        while (ary[right] > pivot) {
            right--;
            (*comparableNum)++;
        }
        if (left > right) {
            break;
        }
        SWAP(ary[right], ary[left]);
        (*changeNum)++;
        left++;
        right--;
    }
    // 上のwhile文が終わった時に必ずleftとrightは隣り合い、
    // left>rightとなる
    // printf("小:");
    showAry(ary, leftIndex, right);
    // printf("大:");
    showAry(ary, left, rightIndex);
    // printf("\n");
    partitioning(ary, leftIndex, right, comparableNum, changeNum);
    partitioning(ary, left, rightIndex, comparableNum, changeNum);
}

int choicePivot(int ary[], int left, int right, int* comparableNum) {
    int center;
    center = (right - left) / 2 + left;
    // printf("ary[left]:%d, ary[center]:%d, ary[right]:%dのため", ary[left],
    // ary[center], ary[right]);
    (*comparableNum)++;
    // 3つの要素を比較して中央値を選択
    // あまりスマートではないが、これ以外の方法がわからなかった。なにかいい方法があれば教えてください。
    if (ary[right] > ary[center]) {
        (*comparableNum)++;
        if (ary[center] > ary[left]) {
            // printf("ary[center]:%dをピボットとする。\n", ary[center]);
            return ary[center];
        } else {
            // printf("ary[left]:%dをピボットとする。\n", ary[left]);
            return ary[left];
        }
    }
    (*comparableNum)++;
    if (ary[center] > ary[left]) {
        (*comparableNum)++;
        if (ary[left] > ary[right]) {
            // printf("ary[left]:%dをピボットとする。\n", ary[left]);
            return ary[left];
        }
        (*comparableNum)++;
        if (ary[left] < ary[right]) {
            // printf("ary[right]:%dをピボットとする。\n", ary[right]);
            return ary[right];
        }
    }
    (*comparableNum)++;
    if (ary[left] > ary[right]) {
        (*comparableNum)++;
        if (ary[right] > ary[center]) {
            // printf("ary[right]:%dをピボットとする。\n", ary[right]);
            return ary[right];
        }
        (*comparableNum)++;
        if (ary[right] < ary[center]) {
            // printf("ary[center]:%dをピボットとする。\n", ary[center]);
            return ary[center];
        }
    }
    // 三つの要素のどれかが同じだとこの処理に入る。今回は要素数が50なのでこの処理には入ることはあまりない。
    // printf("ary[left]:%dをピボットとする。\n", ary[left]);
    return ary[left];
}

void bubblesort(int ary[], int left, int right, int* comparableNum,
                int* changeNum) {
    // printf("バブルソート開始\n");
    // printf("ソート前:");
    showAry(ary, left, right);
    int i, j;
    for (i = left; i < right + 1; i++) {
        (*comparableNum)++;
        for (j = left; j < right - i + left; j++) {
            // j < right - i + left で+leftをしている理由は、
            // このバブルソートではjは0ではなく
            // leftから始まっているからである。
            (*comparableNum)++;
            if (ary[j] > ary[j + 1]) {
                (*changeNum)++;
                SWAP(ary[j], ary[j + 1]);
            }
        }
    }
    // printf("ソート後:");
    showAry(ary, left, right);
    // printf("バブルソート終了\n\n");
}

bool checkSort(int ary[]) {
    int i = 0;
    for (i = 0; i < indexNum - 1; i++) {
        if (ary[i] > ary[i + 1]) {
            return false;
        }
    }
    return true;
}

void makeRandomAry(int ary[]) {
    int i;
    for (i = 0; i < indexNum; i++) {
        ary[i] = rand() % 50000;
    }
}

void showAry(int ary[], int left, int right) {
    int i;
    // printf("[ ");
    for (i = left; i < right + 1; i++) {
        // printf("%d ", ary[i]);
    }
    // printf("]\n");
}
#endif