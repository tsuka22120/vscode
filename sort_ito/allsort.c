#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define C 523
#define index_num 12
#define SWAP(a, b) ((a != b) && (a += b, b = a - b, a -= b))

bool CheckSort(long ary[]);

void bogosort(long ary[]);

void selectionsort(long ary[]);

void heapsort(long ary[]);

void bubblesort(long ary[]);

void quicksort(long ary[]);

void MakeRandomAry(long ary[]);

void shuffle(long ary[]);

// 引数はスタートした時間
void showTime(clock_t start, clock_t end);

void showAry(long ary[], int size);

int main(void) {
    long num[index_num];
    srand((unsigned int)time(NULL));
    MakeRandomAry(num);
    bogosort(num);
    selectionsort(num);
    heapsort(num);
    bubblesort(num);
    quicksort(num);
    return 0;
}

bool CheckSort(long ary[]) {
    int i = 0;
    for (i = 0; i < index_num - 1; i++) {
        if (ary[i] >= ary[i + 1]) {
            return false;
        }
    }
    return true;
}

void bogosort(long ary[]) {
    printf("ボゴソート開始\n");
    long comparableNum = 0;
    clock_t start, end;
    long num[index_num];
    memcpy(num, ary, sizeof(long) * (index_num));
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

void selectionsort(long ary[]) {
    printf("選択ソート開始\n");
    long comparableNum = 0;
    clock_t start, end;
    int minimumNum = 0;
    int i, j;
    long num[index_num];
    memcpy(num, ary, sizeof(long) * (index_num));
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

void heapsort(long ary[]) {
    printf("ヒープソート開始\n");
    long comparableNum = 0;
    clock_t start, end;
    int i;
    long heap[index_num];
    int heap_size = 1;
    int index, childIndex;
    long ans[index_num];
    long num[index_num];
    memcpy(num, ary, sizeof(long) * (index_num));
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

void bubblesort(long ary[]) {
    printf("バブルソート開始\n");
    int i, j;
    long comparableNum = 0;
    clock_t start, end;
    long num[index_num];
    memcpy(num, ary, sizeof(long) * (index_num));
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

void quicksort(long ary[]){
    printf("クイックソート開始\n");
    long left,right;
    
}

void MakeRandomAry(long ary[]) {
    int i;
    for (i = 0; i < index_num; i++) {
        ary[i] = i + 1;
    }
    shuffle(ary);
}

void shuffle(long ary[]) {
    int i;
    int j;
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

void showAry(long ary[], int size) {
    int i;
    printf("[ ");
    for (i = 0; i < size; i++) {
        printf("%ld ", ary[i]);
    }
    printf("]\n");
}