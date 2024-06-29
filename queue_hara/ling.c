#include <stdio.h>

#define QUEUE_SIZE 5

typedef struct {
    int data[QUEUE_SIZE];  // データが入る配列
    int wp;                // 次にデータを入れる場所の配列番号
    int quantity;          // データの個数
} Queue;


int dequeueIndex(Queue obj) {
    if (obj.wp - obj.quantity < 0) {
        return QUEUE_SIZE + obj.wp - obj.quantity;
    } else {
        return obj.wp - obj.quantity;
    }
}

/// @brief キューにデータを積み上げる
/// @param obj データを追加するキューの構造体のアドレス
/// @param data キューに格納するデータ
/// @return
/// 実行の成否を返す。成功:-100,残領域がない:-101,0以下の値が入力された:-102
int enqueue(Queue *obj, int data) {
    // 残り領域があるか確認する
    if (obj->quantity >= QUEUE_SIZE) {
        // 残り領域がない場合はエラーコードを返す
        return -101;
    }
    // データが自然数か確認する
    if (data <= 0) {
        // 自然数でない場合はエラーコードを返す
        return -102;
    }
    // 配列のキューにデータを保存する
    obj->data[obj->wp] = data;
    // キューのポインタをインクリメントする
    obj->quantity++;
    if (obj->wp == QUEUE_SIZE - 1) {
        obj->wp = 0;
    } else {
        obj->wp++;
    }
    // 返り値を返す
    return -100;
}

/// @brief キューからデータを取り出す
/// @param obj データを取り出すキューの構造体のアドレス
/// @return
/// 取り出したデータ,もしくはエラーコード（取り出せるデータがなかった時:-201）
int dequeue(Queue *obj) {
    int index;
    index = dequeueIndex(*obj);
    // データが存在するかどうか確認する．
    if (obj->quantity == 0) {
        // データが存在しない場合はエラーコードを返す．
        return -201;
    }
    // キューからデータをとりだす．
    int data = obj->data[index];
    // 取り出されたデータ部分を埋めるように再構築する
    obj->data[index] = 0;
    // データの個数のカウントを減らす．
    obj->quantity--;
    // データを返す．
    return data;
}

/// @brief キュー用の配列を0で初期化する。
/// @param obj キューの構造体のアドレス
/// @return 成功したら-400を返す。
int initQueue(Queue *obj) {
    int i;
    // キューのデータを入れる配列をすべて 0 に初期化する．
    for (i = 0; i < QUEUE_SIZE; i++) {
        obj->data[i] = 0;
    }
    // キューのデータ格納個数を 0 に初期化する
    obj->quantity = 0;
    // キューの wp ポインタを 0 に初期化する．
    obj->wp = 0;
    return -400;
}

/// @brief キューのデータを表示する
/// @param obj キューの構造体のアドレス
/// @return 成功したら-500を返す。
int showQueue(Queue *obj) {
    int i;
    // 配列全体のデータを順に表示する．
    // データとデータの間に区切り文字「|」を表示する．
    printf("|");
    for (i = 0; i < QUEUE_SIZE; i++) {
        printf("%d", obj->data[i]);
        printf("|");
    }
    return -500;
}

void showResult(int result) {
    switch (result) {
        case -100:
            printf("格納成功\n");
            break;
        case -101:
            printf("残領域がない\n");
            break;
        case -102:
            printf("0以下の値が入力された\n");
            break;
        case -201:
            printf("取り出せるデータがない\n");
            break;
        case -400:
            printf("初期化成功\n");
            break;
        case -500:
            printf("表示成功\n");
            break;
        default:
            printf("取出成功\n");
            break;
    }
    // result の値に応じて，対応するエラーメッセージを表示する．
}

int main() {
    Queue queue;
    int i;
    // キューの初期化
    initQueue(&queue);

    showQueue(&queue);
    // データがいっぱいになった時の挙動を確認
    for (i = 1; i <= 6; i++) {
        printf("<%d", i);
        showResult(enqueue(&queue, i));
        showQueue(&queue);
    }

    for (i = 0; i < 6; i++) {
        printf(">%d", queue.data[dequeueIndex(queue)]);
        showResult(dequeue(&queue));
        showQueue(&queue);
    }
    printf("<%d", 0);
    showResult(enqueue(&queue, 0));
    showQueue(&queue);
    for(i = 0;i < 100;i++){
        printf("<%d", i);
        showResult(enqueue(&queue, i));
        showQueue(&queue);
        printf(">%d", queue.data[dequeueIndex(queue)]);
        showResult(dequeue(&queue));
        showQueue(&queue);
    }
    return 0;
}