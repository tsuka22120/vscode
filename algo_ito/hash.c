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
    int num, sum = 0;
    while (1) {
        c = fgetc(from);
        printf("%c\n",c);
        if (c == EOF) break;
        if('\n' == c){
            fprintf(to,"%d\n",hash(sum));
        }
        num = ascii(c);
        if (num >= 65 && num <= 90) {
            sum += num;
        }
    }
    return 0;
}