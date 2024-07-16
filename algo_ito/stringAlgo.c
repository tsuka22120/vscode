#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100

/// @brief 文字列を比較する
/// @param str1 比較する文字列1
/// @param str2 比較する文字列2
/// @return 同じ文字列なら0、異なる文字列なら-1
int cmpStrings(char str1[], char str2[]) {
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    return -1;
}

int main(void) {
    char str1[MAX], str2[MAX];
    int scanf_ret;
    int str1_len, str2_len, i, j, count = 0;
    printf("被検索文字列を入力してください(%d字以内しか読み込まれません)\n",
           MAX);
    fgets(str1, MAX, stdin);
    if (str1[MAX - 1] == '\000') {
        printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n",
               MAX);
        scanf("%*s%100s", str2);
    } else {
        printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n",
               MAX);
        scanf("%99s", str2);
    }
    printf("被検索文字列: [ %s ]\n", str1);
    printf("検索文字列: [ %s ]\n", str2);
    for (i = 0; i < strlen(str1); i++) {
        for (j = 0; j < strlen(str2); j++) {
            if (str1[i + j] == str2[j]) {
                if (j == strlen(str2) - 1) {
                    printf("検索文字列は%d番目にあります\n", i);
                    count++;
                }
            } else {
                break;
            }
        }
    }
    if (count == 0) {
        printf("検索文字列はありません\n");
        return -1;
    } else {
        return 0;
    }
}