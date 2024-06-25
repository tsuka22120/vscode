// 出席番号:22番
// 氏名:塚田 勇人
// 課題内容:0以上500未満の乱数50個を自作のクイックソートを
// 使ってソートする。またソートをする際、過程がわかるように
// 出力する。
// また追加機能、工夫点として比較階数を測る機能、交換回数を測る機能、
// ピボットをできるだけ中央値に近い値をとれるようにする工夫、
//

#define index_num 50
#define print_on
#define SWAP(a, b) ((a != b) && (a += b, b = a - b, a -= b))

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool checkSort(int ary[]);

void quicksort(int ary[]);

void partitioning(int ary[], int left, int right, int* comparableNum,
                  int* chaneNum);

int choicePivot(int ary[], int left, int right, int* comparableNum);

void bubblesort(int ary[], int left, int right, int* comparableNum,
                int* changeNum);

void makeRandomAry(int ary[]);

void showAry(int ary[], int left, int right);

int main(void) {
    srand((unsigned int)time(NULL));
    int ary[index_num];
    makeRandomAry(ary);
    quicksort(ary);
    return 0;
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
    for (i = left; i <= right; i++) {
        printf("%d ", ary[i]);
    }
    printf("]\n");
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

void quicksort(int ary[]) {
    printf("~~クイックソート開始~~\n\n");
    int left, right;
    int comparableNum = 0, changeNum = 0;
    clock_t start, end;
#ifdef print_on
    printf("ソート前:");
    showAry(ary, 0, index_num - 1);
    printf("\n");
#endif
    start = clock();
    left = 0;
    right = index_num - 1;
    partitioning(ary, left, right, &comparableNum, &changeNum);
    end = clock();
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
    if (right - left < 5) {
        bubblesort(ary, left, right, comparableNum, changeNum);
        return;
    }
    int pivot;
    int leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
#ifdef print_on
    printf("パーティション分割前:");
    showAry(ary, left, right);
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
#ifdef print_on
    printf("小:");
    showAry(ary, leftIndex, left - 1);
    printf("大:");
    showAry(ary, left, rightIndex);
#endif
    partitioning(ary, leftIndex, left - 1, comparableNum, changeNum);
    partitioning(ary, right + 1, rightIndex, comparableNum, changeNum);
}

void bubblesort(int ary[], int left, int right, int* comparableNum,
                int* changeNum) {
    printf("バブルソート開始\n");
    int i, j;
    printf("ソート前:");
    showAry(ary, left, right);
    for (i = left; i < right + 1; i++) {
        (*comparableNum)++;
        for (j = left; j < right - i; j++) {
            (*comparableNum)++;
            if (ary[j] > ary[j + 1]) {
                (*changeNum)++;
                SWAP(ary[j], ary[j + 1]);
            }
        }
    }
    printf("ソート後:");
    showAry(ary, left, right);
    printf("バブルソート終了\n");
}

int choicePivot(int ary[], int left, int right, int* comparableNum) {
    int center;
    center = (right - left) / 2 + left;
#ifdef print_on
    printf("left:%d, center:%d, right:%dのため", ary[left], ary[center],
           ary[right]);
#endif
    (*comparableNum)++;
    if (ary[right] > ary[center]) {
        (*comparableNum)++;
        if (ary[center] > ary[left]) {
#ifdef print_on
            printf("center:%dをピボットとする。\n", ary[center]);
#endif
            return ary[center];
        } else {
#ifdef print_on
            printf("left:%dをピボットとする。\n", ary[left]);
#endif
            return ary[left];
        }
    }
    (*comparableNum)++;
    if (ary[center] > ary[left]) {
        (*comparableNum)++;
        if (ary[left] > ary[right]) {
#ifdef print_on
            printf("left:%dをピボットとする。\n", ary[left]);
#endif
            return ary[left];
        }
        (*comparableNum)++;
        if (ary[left] < ary[right]) {
#ifdef print_on
            printf("right:%dをピボットとする。\n", ary[right]);
#endif
            return ary[right];
        }
    }
    (*comparableNum)++;
    if (ary[left] > ary[right]) {
        (*comparableNum)++;
        if (ary[right] > ary[center]) {
#ifdef print_on
            printf("right:%dをピボットとする。\n", ary[right]);
#endif
            return ary[right];
        }
        (*comparableNum)++;
        if (ary[right] < ary[center]) {
#ifdef print_on
            printf("center:%dをピボットとする。\n", ary[center]);
#endif
            return ary[center];
        }
    }
#ifdef print_on
    printf("left:%dをピボットとする。\n", ary[left]);
#endif
    return ary[left];
}