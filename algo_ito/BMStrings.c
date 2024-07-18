#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100
#define SKIPTABLENUM 0x7e - 0x20

void makeSkipTable(char strings[], char searchWord[]);

int main(void) {
    char strings[MAX + 1], searchWord[MAX + 1];
    int str1_len, str2_len, i, j, count = 0;
    printf("被検索文字列を入力してください(%d字以内しか読み込まれません)\n",
           MAX);
    scanf("%100s", strings);
    printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n", MAX);
    if (strings[MAX - 1] != '\000') {
        scanf("%*s");
        scanf("%100s", searchWord);
    } else {
        scanf("%100s", searchWord);
    }
    printf("被検索文字列: [ %s ]\n", strings);
    printf("検索文字列: [ %s ]\n", searchWord);
    makeSkipTable(strings, searchWord);
}

void makeSkipTable(char strings[], char searchWord[]) {
    int skipTable[SKIPTABLENUM];
    int i, j;
    for (i = 0; i < SKIPTABLENUM; i++) {
        for (j = 0; j < strlen(searchWord); j++) {
            if ((char)(0x20 + i) == searchWord[j]) {
                skipTable[i] = strlen(searchWord) - j;
            } else {
                skipTable[i] = strlen(searchWord);
            }
        }
    }
    for (i = 1; i < SKIPTABLENUM + 1; i++) {
        printf("%c:%d ", 0x20 + i - 1, skipTable[i - 1]);
        if (0 == i % 9) {
            printf("\n");
        }
    }
}