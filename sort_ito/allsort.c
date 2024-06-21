#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define index_num 50
#define print_on
#define SWAP(a, b) ((a != b) && (a += b, b = a - b, a -= b))

bool CheckSort(int64_t ary[]);

void bogosort(int64_t ary[]);

void selectionsort(int64_t ary[]);

void heapsort(int64_t ary[]);

void bubblesort(int64_t ary[]);

void quicksort(int64_t ary[]);

void MakeRandomAry(int64_t ary[]);

int choicePivot(int64_t ary[], int64_t left, int64_t right, int* comparableNum);

/// @brief leftとrightの真ん中を返す関数
/// @param left 配列の左端の添え字
/// @param right 配列の右端の添え字
/// @return 配列の真ん中の添え字
int choiceCenter(int64_t left, int64_t right);

void shuffle(int64_t ary[]);

/// @brief パーティション分割する関数
/// @param ary 配列全体
/// @param left 配列の分割する部分の左端
/// @param right 配列の分割する部分の右端
/// @param comparableNum 試行回数のポインタ
void partitioning(int64_t ary[], int64_t left, int64_t right,
                  int64_t* comparableNum);
// 引数はスタートした時間
void showTime(clock_t start, clock_t end);

void showAry(int64_t ary[], int64_t size);

int main(void) {
    int64_t num[index_num];
    srand((unsigned int)time(NULL));
    MakeRandomAry(num);
    // bogosort(num);
    // selectionsort(num);
    // heapsort(num);
    // bubblesort(num);
    quicksort(num);
    return 0;
}

bool CheckSort(int64_t ary[]) {
    int64_t i = 0;
    for (i = 0; i < index_num - 1; i++) {
        if (ary[i] >= ary[i + 1]) {
            return false;
        }
    }
    return true;
}

void bogosort(int64_t ary[]) {
    printf("ボゴソート開始\n");
    int64_t comparableNum = 0;
    clock_t start, end;
    int64_t num[index_num];
    memcpy(num, ary, sizeof(int64_t) * (index_num));
    printf("ソート前");
    showAry(num, index_num);
    start = clock();
    while (true) {
        shuffle(num);
        comparableNum++;
        if (CheckSort(num) == true) {
            break;
        }
    }
    end = clock();
    printf("ソート後");
    showAry(num, index_num);
    printf("試行回数:%ld\n", comparableNum);
    showTime(start, end);
    printf("ボゴソート終了\n");
}

void selectionsort(int64_t ary[]) {
    printf("選択ソート開始\n");
    int64_t comparableNum = 0;
    clock_t start, end;
    int64_t minimumNum = 0;
    int64_t i, j;
    int64_t num[index_num];
    memcpy(num, ary, sizeof(int64_t) * (index_num));
    printf("ソート前");
    showAry(num, index_num);
    start = clock();
    for (j = 0; j < index_num; j++) {
        for (i = 1 + j; i < index_num; i++) {
            comparableNum++;
            if (num[minimumNum] > num[i]) {
                minimumNum = i;
            }
        }
        SWAP(num[minimumNum], num[j]);
        minimumNum = j + 1;
    }
    end = clock();
    if (CheckSort(num) == false) {
        printf("error\n");
        printf("\n");
    } else {
        printf("ソート後");
        showAry(num, index_num);
        printf("試行回数:%ld\n", comparableNum);
        showTime(start, end);
        printf("選択終了\n");
    }
}

void heapsort(int64_t ary[]) {
    printf("ヒープソート開始\n");
    int64_t comparableNum = 0;
    clock_t start, end;
    int64_t i;
    int64_t heap[index_num];
    int64_t heap_size = 1;
    int64_t index, childIndex;
    int64_t ans[index_num];
    int64_t num[index_num];
    memcpy(num, ary, sizeof(int64_t) * (index_num));
    printf("ソート前");
    showAry(num, index_num);
    start = clock();
    heap[0] = num[0];
    for (i = 1; i < index_num; i++) {
        heap_size++;
        heap[i] = num[i];
        index = i;
        while (true) {
            comparableNum++;
            if (heap[index] < heap[(index - 1) / 2]) {
                SWAP(heap[index], heap[(index - 1) / 2]);
                index = (index - 1) / 2;
            } else {
                break;
            }
            if (index == 0) {
                break;
            }
        }
    }
    for (i = 0; i < index_num; i++) {
        heap_size--;
        ans[i] = heap[0];
        heap[0] = heap[heap_size];
        index = 0;
        while (1) {
            comparableNum++;
            if (heap_size <= 1) {
                childIndex = heap_size;
            } else if (heap[index * 2 + 1] < heap[index * 2 + 2]) {
                childIndex = index * 2 + 1;
            } else {
                childIndex = index * 2 + 2;
            }
            if (heap[index] > heap[childIndex]) {
                SWAP(heap[index], heap[childIndex]);
                index = childIndex;
            } else {
                break;
            }
            if (index * 2 + 1 >= heap_size) {
                break;
            }
        }
    }
    end = clock();
    if (CheckSort(ans) == false) {
        printf("error\n");
        printf("\n");
    } else {
        printf("ソート後");
        showAry(ans, index_num);
        printf("試行回数:%ld\n", comparableNum);
        showTime(start, end);
        printf("ヒープソート終了\n");
    }
}

void bubblesort(int64_t ary[]) {
    printf("バブルソート開始\n");
    int64_t i, j;
    int64_t comparableNum = 0;
    clock_t start, end;
    int64_t num[index_num];
    memcpy(num, ary, sizeof(int64_t) * (index_num));
    printf("ソート前");
    showAry(num, index_num);
    start = clock();
    for (i = 0; i < index_num; i++) {
        comparableNum++;
        for (j = 0; j < index_num - 1 - i; j++) {
            comparableNum++;
            if (num[j] > num[j + 1]) {
                SWAP(num[j], num[j + 1]);
            }
        }
    }
    end = clock();
    if (CheckSort(num) == false) {
        printf("error\n");
        printf("\n");
    } else {
        printf("ソート後");
        showAry(num, index_num);
        printf("試行回数:%ld\n", comparableNum);
        showTime(start, end);
        printf("バブルソート終了\n");
    }
}

void quicksort(int64_t ary[]) {
    printf("クイックソート開始\n");
    int64_t left, right;
    int64_t comparableNum = 0;
    clock_t start, end;
    int64_t num[index_num];
    memcpy(num, ary, sizeof(int64_t) * (index_num));
    printf("ソート前");
    showAry(num, index_num);
    start = clock();
    left = 0;
    right = index_num - 1;
    partitioning(num, left, right, &comparableNum);
    end = clock();
    if (CheckSort(num) == false) {
        printf("error\n");
        printf("\n");
    } else {
        printf("ソート後");
        showAry(num, index_num);
        printf("試行回数:%ld\n", comparableNum);
        showTime(start, end);
        printf("クイックソート終了\n");
    }
}

void partitioning(int64_t ary[], int64_t left, int64_t right,
                  int64_t* comparableNum) {
    if (left >= right) {
        return;
    }
    int64_t pivot;
    int64_t leftIndex, rightIndex;
    leftIndex = left;
    rightIndex = right;
    pivot = choicePivot(ary, left, right, comparableNum);
    while (1) {
        *comparableNum++;
        while (ary[left] < pivot) {
            left++;
            *comparableNum++;
        }
        *comparableNum++;
        while (ary[right] > pivot) {
            right--;
            *comparableNum++;
        }
        if (left >= right) {
            break;
        }
        SWAP(ary[right], ary[left]);
        left++;
        right--;
    }
    printf("%ld\n", *comparableNum);
    partitioning(ary, leftIndex, left - 1, comparableNum);
    partitioning(ary, right + 1, rightIndex, comparableNum);
}

int choicePivot(int64_t ary[], int64_t left, int64_t right,
                int* comparableNum) {
    int64_t center;
    center = (right - left) / 2 + left;
    *comparableNum++;
    if (ary[right] > ary[center]) {
        *comparableNum++;
        if (ary[center] > ary[left]) {
            return ary[center];
        } else {
            return ary[left];
        }
    }
    *comparableNum++;
    if (ary[center] > ary[left]) {
        *comparableNum++;
        if (ary[left] > ary[right]) {
            return ary[left];
        }
        *comparableNum++;
        if (ary[left] < ary[right]) {
            return ary[right];
        }
    }
    *comparableNum++;
    if (ary[left] > ary[right]) {
        *comparableNum++;
        if (ary[right] > ary[center]) {
            return ary[right];
        }
        *comparableNum++;
        if (ary[right] < ary[center]) {
            return ary[center];
        }
    }
    return ary[left];
}

void MakeRandomAry(int64_t ary[]) {
    int64_t i;
    for (i = 0; i < index_num; i++) {
        ary[i] = i + 1;
    }
    shuffle(ary);
}

void shuffle(int64_t ary[]) {
    int64_t i;
    int64_t j;
    for (i = 0; i < index_num; i++) {
        j = rand() % index_num;
        SWAP(ary[i], ary[j]);
    }
}

void showTime(clock_t start, clock_t end) {
    int min, hour;
    double sec;
    sec = (end - start) / (double)CLOCKS_PER_SEC;
    if (sec >= 3600) {
        hour = (int)sec / 3600;
        sec /= 3600;
        min = (int)sec / 60;
        sec /= 60;
        printf("実行時間:%d時間%d分%g秒\n", hour, min, sec);
    } else if (sec >= 60) {
        min = (int)sec / 60;
        sec /= 60;
        printf("実行時間:%d分%g秒\n", min, sec);
    } else {
        printf("実行時間:%.7f秒\n", sec);
    }
}

void showAry(int64_t ary[], int64_t size) {
#ifdef print_on
    int64_t i;
    printf("[ ");
    for (i = 0; i < size; i++) {
        printf("%ld ", ary[i]);
    }
    printf("]\n");
#endif
}