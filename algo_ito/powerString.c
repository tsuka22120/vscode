#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100

int main(void) {
    char str1[MAX], str2[MAX];
    int str1_len, str2_len, i, j, count = 0;
    printf("被検索文字列を入力してください(%d字以内しか読み込まれません)\n",
           MAX);
    scanf("%99s", str1);
    str1[strcspn(str1, "\n")] = '\000';
    printf("検索文字列を入力してください(%d字以内しか読み込まれません)\n", MAX);
    if (str1[MAX - 2] != '\000') {
        scanf("%*s");
        scanf("%99s", str2);
    } else {
        scanf("%99s", str2);
    }
    printf("被検索文字列: [ %s ]\n", str1);
    printf("検索文字列: [ %s ]\n", str2);
    for (i = 0; i < strlen(str1); i++) {
        for (j = 0; j < strlen(str2); j++) {
            if (str1[i + j] == str2[j]) {
                if (j == strlen(str2) - 1) {
                    printf("検索文字列は%d番目にあります:", i);
                    count++;
                    if (i > 1) {
                        printf("[ %c%c \"", str1[i - 2], str1[i - 1]);
                    } else {
                        printf("[ \"");
                    }
                    for (int k = i; k < i + strlen(str2); k++) {
                        printf("%c", str1[k]);
                    }
                    if (i < strlen(str1) - strlen(str2)) {
                        printf("\" %c%c ]\n", str1[i + strlen(str2)],
                               str1[i + strlen(str2) + 1]);
                    } else {
                        printf("\" ]\n");
                    }
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