#include <stdio.h>

#define QUEUE_SIZE 4

int queue[QUEUE_SIZE]; // キュー用の配列
int quantity = 0; // キューに格納されているデータの個数

/// @brief キューにデータを積み上げる
/// @param data キューに格納するデータ
/// @return
/// 実行の成否を返す。成功:-100,残領域がない:-101,0以下の値が入力された:-102
int enqueue(int data) {
    // 残り領域があるか確認する
    if (quantity >= QUEUE_SIZE) {
        // 残り領域がない場合はエラーコードを返す
        return -101;
    }
    // データが自然数か確認する
    if (data <= 0) {
        // 自然数でない場合はエラーコードを返す
        return -102;
    }
    // 配列のキューにデータを保存する
    queue[quantity] = data;
    // キューのポインタをインクリメントする
    quantity++;
    // 返り値を返す
    return -100;
}

/// @brief キューからデータを取り出す
/// @return
/// 取り出したデータ,もしくはエラーコード（取り出せるデータがなかった時:-201）
int dequeue(void) {
    // データが存在するかどうか確認する．
    if (quantity == 0) {
        // データが存在しない場合はエラーコードを返す．
        return -201;
    }
    // キューからデータをとりだす．
    int data = queue[0];
    // データの個数カウントを減らす
    quantity--;
    // 取り出されたデータ部分を埋めるように再構築する
    for (int i = 0; i < quantity; i++) {
        queue[i] = queue[i + 1];
    }
    queue[quantity] = 0;
    // データを返す
    return data;
}

/// @brief キュー用の配列を0で初期化する。
/// @return 成功したら0を返す。
int initQueue() {
    // キューのデータを入れる配列をすべて 0 に初期化する．
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue[i] = 0;
    }
    // 格納データ個数を 0 に初期化する．
    quantity = 0;
    return 0;
}

int showQueue() {
    // 配列全体のデータを順に表示する．
    printf("|");
    for (int i = 0; i < QUEUE_SIZE; i++) {
        printf("%d", queue[i]);
        // データとデータの間に区切り文字「|」を表示する．
        printf("|");
    }
    return 0;
}

void showResult(int result) {
    // result の値に応じて，対応するエラーメッセージを表示する．
    switch (result) {
        case -100:
            printf(":Enqueue success\n");
            break;
        case -101:
            printf(":Enqueue error:No space left(ErrorCode-101)\n");
            break;
        case -102:
            printf(":Enqueue error:Not natural number was entered:(ErrorCode-102)\n");
            break;
        case -201:
            printf(":Dequeue error:Nothing data(ErrorCode-201)\n");
            break;
        case 0:
            printf(":success\n");
            break;
        default:
            printf(":Dequeue success\n");
            break;
    }
}

int main() {
    int i;
    int dequeueData, dequeueResult;
    // キューの初期化
    printf("Queue initialize");
    showResult(initQueue());
    // キューにデータを積み上げる
    for (i = 1; i <= 5; i++) {
        showQueue();
        printf("<--%d", i);
        showResult(enqueue(i));
    }
    // キューのデータを表示する
    // キューからデータを取り出す
    for (i = 0; i < 5; i++) {
        dequeueData = queue[0];
        dequeueResult = dequeue();
        showQueue();
        printf("-->%d", dequeueData);
        showResult(dequeueResult);
    }
    // キューのデータを表示する
    for(i = 2; i >= 0;i--){
        showQueue();
        printf("<--%d", i);
        showResult(enqueue(i));
    }
    return 0;
}