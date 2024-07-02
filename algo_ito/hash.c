#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/// @brief hash化する関数
/// @param key ハッシュする値
/// @return ハッシュ化された値
int hash(int key) { return key % MAX; }

/// @brief 文字をASCIIコードに変換する関数
/// @param c 文字
/// @return ASCIIコード
int ascii(char c) { return (int)c; }

int main() {
    FILE *from, *to;
    from = fopen("dist.all.last.txt", "r");
    to = fopen("hash.txt", "w");
    char c;
    while (1) {
        c = fgetc(from);
        if (c == EOF) break;
        c = ascii(c);
        if (c >= 65 && c <= 90) {
            fprintf(to, "%d\n", hash(c));
            printf("%d\n", hash(c));
        }
    }
    return 0;
}