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

#define index_num 50     // 要素数
#define count_num 1000   // 試行回数
#define sortTypen_num 4  // ソートの種類の数
#define switchMAX_num 10  // クイックソートから切り替える要素数の最大値
#define switchMIN_num 5  // クイックソートから切り替える要素数の最小値
#define SWAP(a, b) (a += b, b = a - b, a -= b)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int bogosortComparableNum;
    int bogosortChangeNum;
    int selectionsortComparableNum;
    int selectionsortChangeNum;
    int heapsortComparableNum;
    int heapsortChangeNum;
    int bubblesortComparableNum;
    int bubblesortChangeNum;
} Sort;

/// @brief クイックソートを行う関数
/// @param ary ソートする配列
/// @param sortType ソートの種類
/// @param switchNum クイックソートから切り替える要素数
/// @param CN 比較回数と交換回数を格納する構造体
void quicksort(int ary[], int sortType, int switchNum, Sort* CN);

/// @brief パーティション分割を行う関数
/// @param ary 分割する配列
/// @param left 分割する配列の範囲の左端のインデックス
/// @param right 分割する配列の範囲の右端のインデックス
/// @param sortType ソートの種類
/// @param switchNum クイックソートから切り替える要素数
/// @param CN 比較回数と交換回数を格納する構造体
void partitioning(int ary[], int left, int right, int sortType, int switchNum,
                  Sort* CN);

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

int main(void) {
    // 乱数の種を設定
    int count, switchNum, sortType;
    Sort CN[count_num][switchMAX_num - switchMIN_num + 1][sortTypen_num];
    srand((unsigned int)time(NULL));
    int ary[index_num];
    makeRandomAry(ary);
    for (sortType = 0; sortType < sortTypen_num; sortType++) {
        for (switchNum = 0; switchNum < switchMAX_num - switchMIN_num;
             switchNum++) {
            for (count = 0; count < count_num; count++) {
                quicksort(ary, sortType, switchNum + switchMIN_num,
                          &CN[count][switchNum][0]);
            }
        }
    }
    return 0;
}

void quicksort(int ary[], int sortType, int switchNum, Sort* CN) {
    int left, right;  // ソートする配列の左端:left と右端:right
    left = 0;
    right = index_num - 1;
    partitioning(ary, left, right, sortType, switchNum, CN);
    if (checkSort(ary) == false) {
        printf("error\n");
        printf("\n");
    } else {
        printf("比較回数:%d\n", comparableNum);
        printf("交換回数:%d\n", changeNum);
    }
}

void partitioning(int ary[], int left, int right, int sortType, int switchNum,
                  Sort* CN) {
    // 要素数がswitchNum以下の場合はsortTypeで選ばれているソートを行う
    if (right - left < switchNum) {
        switch (sortType) {
            case 0:
                bubblesort(ary, left, right, CN);
                return;
        }
    }
    int pivot;
    int leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
    // 左右の端のインデックスを保存しておき、再帰呼び出しの際に使う
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
    partitioning(ary, leftIndex, right, comparableNum, changeNum);
    partitioning(ary, left, rightIndex, comparableNum, changeNum);
}

int choicePivot(int ary[], int left, int right, int* comparableNum) {
    int center;
    center = (right - left) / 2 + left;
    (*comparableNum)++;
    // 3つの要素を比較して中央値を選択
    // あまりスマートではないが、これ以外の方法がわからなかった。なにかいい方法があれば教えてください。
    if (ary[right] > ary[center]) {
        (*comparableNum)++;
        if (ary[center] > ary[left]) {
            return ary[center];
        } else {
            return ary[left];
        }
    }
    (*comparableNum)++;
    if (ary[center] > ary[left]) {
        (*comparableNum)++;
        if (ary[left] > ary[right]) {
            return ary[left];
        }
        (*comparableNum)++;
        if (ary[left] < ary[right]) {
            return ary[right];
        }
    }
    (*comparableNum)++;
    if (ary[left] > ary[right]) {
        (*comparableNum)++;
        if (ary[right] > ary[center]) {
            return ary[right];
        }
        (*comparableNum)++;
        if (ary[right] < ary[center]) {
            return ary[center];
        }
    }
    return ary[left];
}

void bubblesort(int ary[], int left, int right, Sort* CN) {
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