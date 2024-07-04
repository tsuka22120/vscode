#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/// @brief hash化する関数
/// @param key ハッシュする値
/// @return ハッシュ化された値
int hash(int key) { return key * key % MAX; }

/// @brief 文字をASCIIコードに変換する関数
/// @param c 文字
/// @return ASCIIコード
int ascii(char c[]) { return (int)c[0]; }

int main() {
    FILE *from, *to;
    int count[100] = {0};
    from = fopen("algo_ito/dist.all.last.txt", "r");
    to = fopen("algo_ito/hash.csv", "w");
    if(from == NULL){
        printf("read file not open!\n");
        return -1;
    }
    if(to == NULL){
        printf("write file not open!\n");
        return -1;
    }
    int num, sum = 0;
    while (1) {
        if ((num = fgetc(from)) == EOF) break;
        if('\n' == num){
            fprintf(to, "%d,\n", hash(sum));
            sum = 0;
        }else if (num >= 65 && num <= 90) {
            sum += num;
        }
    }
    // for (int i = 0; i < MAX; i++) {
    //     fprintf(to, "%d,\n", count[i]);
    // }
    fclose(from);
    fclose(to);
    return 0;
}