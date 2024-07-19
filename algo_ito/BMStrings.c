#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100
#define SKIPTABLENUM 0x7e - 0x20

void makeSkipTable(int skipTable[], char searchWord[], int searchWord_len);

int main(void) {
    char strings[MAX + 1], searchWord[MAX + 1];
    int skipTable[SKIPTABLENUM];
    int strings_len, searchWord_len, i, j, count = 0;
    strings_len = strlen(strings);
    searchWord_len = strlen(searchWord);
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
    makeSkipTable(skipTable, searchWord, searchWord_len);
    for (i = 0; i < strings_len - searchWord_len + 1; i++) {
        for (j = searchWord_len - 1; j >= 0; j--) {
            if (strings[i + j] == searchWord[j]) {
                if (j == 0) {
                    printf("検索文字列が見つかりました(%d文字目)\n", i);
                    break;
                }
            } else {
                i += skipTable[(int)strings[i + j] - 0x20];
            }
        }
    }
    return 0;
}

void makeSkipTable(int skipTable[], char searchWord[], int searchWord_len) {
    int i, j;
    for (i = 0; i < SKIPTABLENUM; i++) {
        for (j = searchWord_len - 2; j >= 0; j--) {
            if ((char)(0x20 + i) == searchWord[j]) {
                skipTable[i] = searchWord_len - j - 1;
                break;
            } else {
                skipTable[i] = searchWord_len;
            }
        }
    }
    for (i = 1; i < SKIPTABLENUM + 1; i++) {
        printf("%c:%2d ", 0x20 + i - 1, skipTable[i - 1]);
        if (0 == i % 9) {
            printf("\n");
        }
    }
}