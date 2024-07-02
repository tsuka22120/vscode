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

#define index_num 10000    // 要素数
#define count_num 10000     // 試行回数
#define sortType_num 4  // ソートの種類の数
#define switchMAX_num 14  // クイックソートから切り替える要素数の最大値
#define switchMIN_num 5  // クイックソートから切り替える要素数の最小値
#define bogoType 0       // ボゴソート
#define selectionType 1  // 選択ソート
#define heapType 2       // ヒープソート
#define bubbleType 3     // バブルソート

#define SWAP(a, b) ((a != b) && (a += b, b = a - b, a -= b))

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int ComparableNum;
    int ChangeNum;
} Sort;

typedef struct {
    float num;
    int sortType;
    int switchNum;
} Average;

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
int choicePivot(int ary[], int left, int right, Sort* CN);

/// @brief ボゴソートを行う関数
/// @param ary ソートする配列
/// @param left ソートする配列の範囲の左端のインデックス
/// @param right ソートする配列の範囲の右端のインデックス
/// @param CN 比較回数と交換回数を格納する構造体
void bogoSort(int ary[], int left, int right, Sort* CN);

/// @brief 選択ソートを行う関数
/// @param ary ソートする配列
/// @param left ソートする配列の範囲の左端のインデックス
/// @param right ソートする配列の範囲の右端のインデックス
/// @param CN 比較回数と交換回数を格納する構造体
void selectionSort(int ary[], int left, int right, Sort* CN);

/// @brief ヒープソートを行う関数
/// @param ary ソートする配列
/// @param left ソートする配列の範囲の左端のインデックス
/// @param right ソートする配列の範囲の右端のインデックス
/// @param CN 比較回数と交換回数を格納する構造体
void heapSort(int ary[], int left, int right, Sort* CN);

void heapify(int ary[], int left, int right, Sort* CN);

/// @brief バブルソートを行う関数
/// @param ary ソートする配列
/// @param left ソートする配列の範囲の左端のインデックス
/// @param right ソートする配列の範囲の右端のインデックス
/// @param CN 比較回数と交換回数を格納する構造体
void bubblesort(int ary[], int left, int right, Sort* CN);

/// @brief ソートが正常に行われているか判定する関数
/// @param ary 判定する配列
/// @return 正常に行われていたらtrue, そうでなければfalse
bool checkSort(int ary[], int left, int right, Sort* CN);

/// @brief 配列を0以上500未満の乱数で生成する関数
/// @param ary 生成する配列
void makeRandomAry(int ary[]);

void shuffle(int ary[], int left, int right, Sort* CN);

void initStruct(Sort* CN);

int main(void) {
    int count, switchNum, sortType;
    int i, j, k;
    int ary[index_num];
    float averageComparableNum = 0, averageChangeNum = 0;
    Sort CN[count_num][switchMAX_num - switchMIN_num + 1][sortType_num];
    Average minComparableNum;
    Average minChangeNum;
    minComparableNum.num = 1000000;
    minChangeNum.num = 1000000;
    for (k = 0; k < count_num; k++) {
        for (i = 0; i < switchMAX_num - switchMIN_num + 1; i++) {
            for (j = 0; j < sortType_num; j++) {
                initStruct(&CN[k][i][j]);
            }
        }
    }
    printf("比較回数と交換回数の平均を計算します\n");
    printf("要素数:%d\n", index_num);
    printf("試行回数:%d\n", count_num);
    printf("%d以上%d以下の要素数になった時に切り替える\n", switchMIN_num,
           switchMAX_num);
    srand((unsigned int)time(NULL));
    for (sortType = bogoType; sortType < sortType_num; sortType++) {
        switch (sortType) {
            case bogoType:
                printf("ボゴソート\n");
                break;
            case selectionType:
                printf("選択ソート\n");
                break;
            case heapType:
                printf("ヒープソート\n");
                break;
            case bubbleType:
                printf("バブルソート\n");
                break;
        }
        for (switchNum = 0; switchNum < switchMAX_num - switchMIN_num + 1;
             switchNum++) {
            printf("要素数が%d以下になった時に切り替える\n",
                   switchNum + switchMIN_num);
            for (count = 0; count < count_num; count++) {
                makeRandomAry(ary);
                quicksort(ary, sortType, switchNum + switchMIN_num,
                          &CN[count][switchNum][sortType]);
                averageComparableNum +=
                    (float)CN[count][switchNum][sortType].ComparableNum;
                averageChangeNum += (float)CN[count][switchNum][sortType].ChangeNum;
            }
            averageComparableNum /= count_num;
            averageChangeNum /= count_num;
            printf("比較回数の平均:%f\n", averageComparableNum);
            printf("交換回数の平均:%f\n\n", averageChangeNum);
            if (averageComparableNum < minComparableNum.num) {
                minComparableNum.num = averageComparableNum;
                minComparableNum.sortType = sortType;
                minComparableNum.switchNum = switchNum + switchMIN_num;
            }
            if (averageChangeNum < minChangeNum.num) {
                minChangeNum.num = averageChangeNum;
                minChangeNum.sortType = sortType;
                minChangeNum.switchNum = switchNum + switchMIN_num;
            }
            averageChangeNum = 0;
            averageComparableNum = 0;
        }
    }
    printf("\n");
    printf("最も比較回数が少ないパターン\n");
    switch (minComparableNum.sortType) {
        case bogoType:
            printf("ボゴソート\n");
            break;
        case selectionType:
            printf("選択ソート\n");
            break;
        case heapType:
            printf("ヒープソート\n");
            break;
        case bubbleType:
            printf("バブルソート\n");
            break;
    }
    printf("要素数が%d以下になった時に切り替える\n",
           minComparableNum.switchNum);
    printf("比較回数の平均:%f\n\n", minComparableNum.num);
    printf("最も交換回数が少ないパターン\n");
    switch (minChangeNum.sortType) {
        case bogoType:
            printf("ボゴソート\n");
            break;
        case selectionType:
            printf("選択ソート\n");
            break;
        case heapType:
            printf("ヒープソート\n");
            break;
        case bubbleType:
            printf("バブルソート\n");
            break;
    }
    printf("要素数が%d以下になった時に切り替える\n", minChangeNum.switchNum);
    printf("交換回数の平均:%f\n", minChangeNum.num);
    return 0;
}

void quicksort(int ary[], int sortType, int switchNum, Sort* CN) {
    int left, right;  // ソートする配列の左端:left と右端:right
    left = 0;
    right = index_num - 1;
    partitioning(ary, left, right, sortType, switchNum, CN);
}
void partitioning(int ary[], int left, int right, int sortType, int switchNum,
                  Sort* CN) {
    // 要素数がswitchNum以下の場合はsortTypeで選ばれているソートを行う
    if (right - left < switchNum) {
        switch (sortType) {
            case bogoType:
                bogoSort(ary, left, right, CN);
                return;
            case selectionType:
                selectionSort(ary, left, right, CN);
                return;
            case heapType:
                heapSort(ary, left, right, CN);
                return;
            case bubbleType:
                bubblesort(ary, left, right, CN);
                return;
        }
    }
    int pivot;
    int leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
    // 左右の端のインデックスを保存しておき、再帰呼び出しの際に使う
    pivot = choicePivot(ary, left, right, CN);
    while (1) {
        (*CN).ComparableNum++;
        while (ary[left] < pivot) {
            left++;
            (*CN).ComparableNum++;
        }
        (*CN).ComparableNum++;
        while (ary[right] > pivot) {
            right--;
            (*CN).ComparableNum++;
        }
        if (left >= right) {
            break;
        }
        SWAP(ary[right], ary[left]);
        (*CN).ChangeNum++;
        left++;
        right--;
    }
    // 上のwhile文が終わった時に必ずleftとrightは隣り合い、
    // left>rightとなる
    partitioning(ary, leftIndex, right, sortType, switchNum, CN);
    partitioning(ary, left, rightIndex, sortType, switchNum, CN);
}

int choicePivot(int ary[], int left, int right, Sort* CN) {
    int center;
    center = (right - left) / 2 + left;
    (*CN).ComparableNum++;
    // printf("left:%d center:%d right:%d\n", left, center, right);
    //  3つの要素を比較して中央値を選択
    //  あまりスマートではないが、これ以外の方法がわからなかった。なにかいい方法があれば教えてください。
    if (ary[right] > ary[center]) {
        (*CN).ComparableNum++;
        if (ary[center] > ary[left]) {
            return ary[center];
        } else {
            return ary[left];
        }
    }
    (*CN).ComparableNum++;
    if (ary[center] > ary[left]) {
        (*CN).ComparableNum++;
        if (ary[left] > ary[right]) {
            return ary[left];
        }
        (*CN).ComparableNum++;
        if (ary[left] < ary[right]) {
            return ary[right];
        }
    }
    (*CN).ComparableNum++;
    if (ary[left] > ary[right]) {
        (*CN).ComparableNum++;
        if (ary[right] > ary[center]) {
            return ary[right];
        }
        (*CN).ComparableNum++;
        if (ary[right] < ary[center]) {
            return ary[center];
        }
    }
    return ary[left];
}

void bogoSort(int ary[], int left, int right, Sort* CN) {
    while (true) {
        shuffle(ary, left, right, CN);
        if (checkSort(ary, left, right, CN) == true) {
            break;
        }
    }
}

void selectionSort(int ary[], int left, int right, Sort* CN) {
    int i, j, min;
    for (i = left; i < right; i++) {
        min = i;
        for (j = i + 1; j < right + 1; j++) {
            (*CN).ComparableNum++;
            if (ary[j] < ary[min]) {
                min = j;
            }
        }
        SWAP(ary[i], ary[min]);
        (*CN).ChangeNum++;
    }
}

void heapSort(int ary[], int left, int right, Sort* CN) {
    int i;
    for (i = right / 2; i >= left; i--) {
        heapify(ary, i, right, CN);
    }
    for (i = right; i > left; i--) {
        SWAP(ary[left], ary[i]);
        (*CN).ChangeNum++;
        heapify(ary, left, i - 1, CN);
    }
}

void heapify(int ary[], int left, int right, Sort* CN) {
    int i, j;
    i = left;
    while (i <= right / 2) {
        j = 2 * i;
        (*CN).ComparableNum += 2;
        if (j < right && ary[j] < ary[j + 1]) {
            j++;
        }
        (*CN).ComparableNum++;
        if (ary[i] >= ary[j]) {
            break;
        }
        SWAP(ary[i], ary[j]);
        (*CN).ChangeNum++;
        i = j;
    }
}

void bubblesort(int ary[], int left, int right, Sort* CN) {
    int i, j;
    for (i = left; i < right + 1; i++) {
        (*CN).ComparableNum++;
        for (j = left; j < right - i + left; j++) {
            // j < right - i + left で+leftをしている理由は、
            // このバブルソートではjは0ではなく
            // leftから始まっているからである。
            (*CN).ComparableNum++;
            if (ary[j] > ary[j + 1]) {
                SWAP(ary[j], ary[j + 1]);
                (*CN).ChangeNum++;
            }
        }
    }
}

bool checkSort(int ary[], int left, int right, Sort* CN) {
    int i = 0;
    for (i = left; i < right; i++) {
        (*CN).ComparableNum++;
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

void shuffle(int ary[], int left, int right, Sort* CN) {
    int i;
    int j;
    for (i = left; i < right + 1; i++) {
        j = rand() % (right + 1 - left) + left;
        SWAP(ary[i], ary[j]);
        (*CN).ChangeNum++;
    }
}

void initStruct(Sort* CN) {
    int i;
    for (i = 0; i < count_num; i++) {
        CN->ComparableNum = 0;
        CN->ChangeNum = 0;
    }
}