#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100
#define SKIPTABLENUM 0x7e - 0x20

void makeSkipTable(int skipTable[], char searchWord[], int searchWord_len);

void initStrings(char strings[], int strings_len) {
    for (int i = 0; i < strings_len; i++) {
        strings[i] = '\000';
    }
}

int main(void) {
    char strings[MAX + 1], searchWord[MAX + 1];
    char gm[1024];

    int skipTable[SKIPTABLENUM];
    int strings_len, searchWord_len, i, j, count = 0;
    initStrings(strings, MAX + 1);
    initStrings(searchWord, MAX + 1);
    initStrings(gm, 1024);
    while (1) {
        printf("被検索文字列を入力してください(%d字以内しか読み込まれません)\n",
               MAX);
        fgets(strings, MAX + 1, stdin);
        strings[strcspn(strings, "\n")] = '\000';
        strings_len = strlen(strings);
        for (i = 0; i < strings_len; i++) {
            if (strings[i] < 0x20 || strings[i] > 0x7e) {
                printf("半角文字を入力してください\n");
                break;
            }
        }
        if (i == strings_len) {
            break;
        }
    }

    printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n", MAX);
    if (strings[MAX - 1] != '\000') {
        fgets(gm, 1024, stdin);
        fgets(searchWord, MAX, stdin);
    } else {
        fgets(searchWord, MAX, stdin);
    }
    searchWord[strcspn(searchWord, "\n")] = '\000';
    while (1) {
        searchWord_len = strlen(searchWord);
        for (i = 0; i < searchWord_len; i++) {
            if (searchWord[i] < 0x20 || searchWord[i] > 0x7e) {
                printf("半角文字を入力してください\n");
                break;
            }
        }
        if (i == searchWord_len) {
            break;
        }
        printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n",
               MAX);
        scanf("%100s", searchWord);
    }
    printf("被検索文字列: [ %s ]\n", strings);
    printf("検索文字列: [ %s ]\n", searchWord);
    searchWord_len = strlen(searchWord);
    makeSkipTable(skipTable, searchWord, searchWord_len);
    for (i = 0; i < strings_len - searchWord_len + 1; i++) {
        for (j = searchWord_len - 1; j >= 0; j--) {
            if (strings[i + j] == searchWord[j]) {
                if (j == 0) {
                    printf("検索文字列が見つかりました(%d文字目):", i + 1);
                    count++;
                    if (i > 1) {
                        printf("[ %c%c \"", strings[i - 2], strings[i - 1]);
                    } else {
                        printf("[ \"");
                    }
                    for (int k = i; k < i + searchWord_len; k++) {
                        printf("%c", strings[k]);
                    }
                    if (i < strings_len - searchWord_len) {
                        printf("\" %c%c ]\n", strings[i + searchWord_len],
                               strings[i + searchWord_len + 1]);
                    } else {
                        printf("\" ]\n");
                    }
                    i += searchWord_len - 1;
                    break;
                }
            } else {
                i += skipTable[(int)strings[i + j] - 0x20] - 1;
                break;
            }
        }
    }
    if (count == 0) {
        printf("検索文字列はありません\n");
    }
    return 0;
}

void makeSkipTable(int skipTable[], char searchWord[], int searchWord_len) {
    int i, j;
    for (i = 0; i < SKIPTABLENUM; i++) {
        for (j = searchWord_len; j >= 0; j--) {
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
    printf("\n");
}