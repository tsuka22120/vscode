#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/// @brief hash化する関数
/// @param key ハッシュする値
/// @return ハッシュ化された値
int hash(int key) { return key / 3 % MAX; }

int main() {
    FILE *from, *to;
    int count[MAX];
    int i;
    int num, sum = 0;
    // 配列の初期化
    for (i = 0; i < MAX; i++) {
        count[i] = 0;
    }
    // ファイルの読み込み
    from = fopen("algo_ito/text/dist.all.last.txt", "r");
    to = fopen("algo_ito/text/hash4.csv", "w");
    if (from == NULL) {
        printf("read file not open!\n");
        return -1;
    }
    if (to == NULL) {
        printf("write file not open!\n");
        return -1;
    }

    while (1) {
        // 1文字ずつ読み込む
        // ファイルの終端に達した場合はループを抜ける
        if ((num = fgetc(from)) == EOF) break;
        if ('\n' == num) { // 改行の場合ハッシュ化してカウントする
            count[hash(sum)]++;
            sum = 0;
        } else if (num >= 65 && num <= 90) { // アルファベットの場合ASCIIコードを数値化して足し合わせる
            sum += num;
        }
    }
    // ファイルへの書き込み
    for (int i = 0; i < MAX; i++) {
        fprintf(to, "%d,\n", count[i]);
    }
    fclose(from);
    fclose(to);
    return 0;
}