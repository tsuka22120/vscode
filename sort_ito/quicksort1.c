// 出席番号:22番
// 氏名:塚田 勇人
// 課題内容:0以上500未満の乱数50個を自作のクイックソートを
// 使ってソートする。またソートをする際、過程がわかるように
// 出力する。
// また追加機能として比較回数を測る機能、交換回数を測る機能、
// ソートの過程を表示するかしないかを選択する機能を追加した。
// 工夫点として分割によって要素数が5以下になった場合に
// バブルソートを行うようにした。また、ピボットの選択において
// 3つの要素を比較して中央値を選択するようにした。

#define index_num 50
#define print_on
#define SWAP(a, b) (a += b, b = a - b, a -= b)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    // 乱数の種を設定
    srand((unsigned int)time(NULL));
    int ary[index_num];
    makeRandomAry(ary);
    quicksort(ary);
    return 0;
}

void quicksort(int ary[]) {
    printf("~~クイックソート開始~~\n\n");
    int left, right;  // ソートする配列の左端:left と右端:right
    int comparableNum = 0, changeNum = 0;  // comparableNum:比較回数 changeNum:交換回数
#ifdef print_on
    printf("ソート前:");
    showAry(ary, 0, index_num - 1);
    printf("\n");
#endif
    left = 0;
    right = index_num - 1;
    partitioning(ary, left, right, &comparableNum, &changeNum);
    if (checkSort(ary) == false) {
        printf("error\n");
        printf("\n");
    } else {
#ifdef print_on
        printf("ソート後:");
        showAry(ary, 0, index_num - 1);
#endif
        printf("比較回数:%d\n", comparableNum);
        printf("交換回数:%d\n", changeNum);
        printf("クイックソート終了\n");
    }
}

void partitioning(int ary[], int left, int right, int* comparableNum,
                  int* changeNum) {
    // 要素数が5以下の場合はバブルソートを行う
    if (right - left < 5) {
        bubblesort(ary, left, right, comparableNum, changeNum);
        return;
    }
    int pivot;
    int leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
    // 左右の端のインデックスを保存しておき、再帰呼び出しの際に使う
#ifdef print_on
    printf("パーティション分割前:");
    showAry(ary, left, right);
    printf("\n");
#endif
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
        if (left >= right) {
            break;
        }
        SWAP(ary[right], ary[left]);
        (*changeNum)++;
        left++;
        right--;
    }
    // 上のwhile文が終わった時に必ずleftとrightは隣り合い、
    // left>rightとなる
#ifdef print_on
    printf("小:");
    showAry(ary, leftIndex, right);
    printf("大:");
    showAry(ary, left, rightIndex);
    printf("\n");
#endif
    partitioning(ary, leftIndex, right, comparableNum, changeNum);
    partitioning(ary, left, rightIndex, comparableNum, changeNum);
}

int choicePivot(int ary[], int left, int right, int* comparableNum) {
    int center;
    center = (right - left) / 2 + left;
#ifdef print_on
    printf("ary[left]:%d, ary[center]:%d, ary[right]:%dのため", ary[left],
           ary[center], ary[right]);
#endif
    (*comparableNum)++;
    // 3つの要素を比較して中央値を選択
    // あまりスマートではないが、これ以外の方法がわからなかった。なにかいい方法があれば教えてください。
    if (ary[right] > ary[center]) {
        (*comparableNum)++;
        if (ary[center] > ary[left]) {
#ifdef print_on
            printf("ary[center]:%dをピボットとする。\n", ary[center]);
#endif
            return ary[center];
        } else {
#ifdef print_on
            printf("ary[left]:%dをピボットとする。\n", ary[left]);
#endif
            return ary[left];
        }
    }
    (*comparableNum)++;
    if (ary[center] > ary[left]) {
        (*comparableNum)++;
        if (ary[left] > ary[right]) {
#ifdef print_on
            printf("ary[left]:%dをピボットとする。\n", ary[left]);
#endif
            return ary[left];
        }
        (*comparableNum)++;
        if (ary[left] < ary[right]) {
#ifdef print_on
            printf("ary[right]:%dをピボットとする。\n", ary[right]);
#endif
            return ary[right];
        }
    }
    (*comparableNum)++;
    if (ary[left] > ary[right]) {
        (*comparableNum)++;
        if (ary[right] > ary[center]) {
#ifdef print_on
            printf("ary[right]:%dをピボットとする。\n", ary[right]);
#endif
            return ary[right];
        }
        (*comparableNum)++;
        if (ary[right] < ary[center]) {
#ifdef print_on
            printf("ary[center]:%dをピボットとする。\n", ary[center]);
#endif
            return ary[center];
        }
    }
#ifdef print_on
// 三つの要素のどれかが同じだとこの処理に入る。今回は要素数が50なのでこの処理には入ることはあまりない。
    printf("ary[left]:%dをピボットとする。\n", ary[left]);
#endif
    return ary[left];
}

void bubblesort(int ary[], int left, int right, int* comparableNum,
                int* changeNum) {
#ifdef print_on
    printf("バブルソート開始\n");
    printf("ソート前:");
    showAry(ary, left, right);
#endif
    int i, j;
    for (i = left; i < right + 1; i++) {
        (*comparableNum)++;
        for (j = left; j < right - i + left; j++) {
            //j < right - i + left で+leftをしている理由は、
            //このバブルソートではjは0ではなく
            //leftから始まっているからである。
            (*comparableNum)++;
            if (ary[j] > ary[j + 1]) {
                (*changeNum)++;
                SWAP(ary[j], ary[j + 1]);
            }
        }
    }
#ifdef print_on
    printf("ソート後:");
    showAry(ary, left, right);
    printf("バブルソート終了\n\n");
#endif
}

bool checkSort(int ary[]) {
    int i = 0;
    for (i = 0; i < index_num - 1; i++) {
        if (ary[i] > ary[i + 1]) {
            return false;
        }
    }
    return true;
}

void makeRandomAry(int ary[]) {
    int i;
    for (i = 0; i < index_num; i++) {
        ary[i] = rand() % 500;
    }
}

void showAry(int ary[], int left, int right) {
    int i;
    printf("[ ");
    for (i = left; i < right + 1; i++) {
        printf("%d ", ary[i]);
    }
    printf("]\n");
}