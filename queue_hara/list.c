#include <stdio.h>
#include <stdlib.h>

struct queue {
    int value;
    struct queue *addr;
};

struct queue *bottom_queue =
    NULL;  // 最古のキューのアドレスを記憶しておくポインタ
struct queue *top_queue = NULL;  // 最新のキューのアドレスを記憶しておくポインタ

/// @brief キューにデータを積み上げる
/// @param data キューに格納するデータ
/// @return
/// 実行の成否を返す。成功:-100,残領域がない:-101,0以下の値が入力された:-102
int enqueue(int data) {
    int r_value = -100;
    struct queue *new_queue;
    if (data <= 0) {
        r_value = -102;
    }

    else if ((new_queue = (struct queue *)malloc(sizeof(struct queue))) ==
             NULL) {
        r_value = -101;
    } else {
        new_queue->value = data;
        new_queue->addr = NULL;
        if (bottom_queue == NULL) {
            bottom_queue = new_queue;
        } else {
            top_queue->addr = new_queue;
        }
        top_queue = new_queue;
    }
    return r_value;
}

/// @brief キューからデータを取り出す
/// @return
/// 取り出したデータ,もしくはエラーコード（取り出せるデータがなかった時:-201,
/// キュ取り出しエラー:-202,その他のエラー:-200)
int dequeue() {
    int r_value = -200;
    struct queue *new_bottom;
    if (top_queue == bottom_queue &&
        bottom_queue != NULL) {  // キューにデータが一つしかない場合
        r_value = bottom_queue->value;
        free(bottom_queue);
        bottom_queue = NULL;
        top_queue = NULL;
    } else if (bottom_queue != NULL &&
               bottom_queue != NULL) {  // キューにデータが複数ある場合
        r_value = bottom_queue->value;
        new_bottom = bottom_queue->addr;
        free(bottom_queue);
        bottom_queue = new_bottom;
    } else if (bottom_queue == NULL) {  // キューにデータがない場合
        r_value = -201;
    } else {  // その他のエラー
        r_value = -202;
    }
    return r_value;
}

/// @brief キュー用の配列のデータを表示する。
/// @return 成功したら0を返す。
int showQueue() {
    struct queue *print_queue;
    print_queue = bottom_queue;
    printf("|");
    while (print_queue != NULL) {
        printf("%d|", print_queue->value);
        print_queue = print_queue->addr;
    }
    return 0;
}

/// @brief エラーメッセージを表示する
/// @param result エラーコード
void showResult(int result) {
    switch (result) {
        case 0:
            printf("Print success\n");
            break;
        case -100:
            printf("Enqueue success\n");
            break;
        case -101:
            printf("Enqueue error: no remaining area(ErrorCode-101)\n");
            break;
        case -102:
            printf(
                "Enqueue error:Enqueue error:Not natural number was "
                "entered:(ErrorCode-102)\n");
            break;
        case -200:
            printf("Dequeue error:Other error(ErrorCode-200)\n");
            break;
        case -201:
            printf("Dequeue error:Nothing data(ErrorCode-201)\n");
            break;
        case -202:
            printf("Dequeue error:Dequeue error(ErrorCode-202)\n");
            break;
        default:
            printf("Dequeue success\n");
            break;
    }
}

/// @brief キューのデータを解放する
void freeQueue() {
    struct queue *this_Queue;
    while (bottom_queue != NULL) {
        this_Queue = bottom_queue->addr;
        free(bottom_queue);
        bottom_queue = this_Queue;
    }
}
int main(void) {
    int i;
    int dequeueData, dequeueResult;
    // データをキューに積み上げる
    for (i = 1; i < 10; i++) {
        showQueue();
        printf("<--%d:", i);
        showResult(enqueue(i));
    }
    // データをキューから取り出す
    for (i = 0; i < 10; i++) {
        dequeueResult = dequeue();
        if (dequeueResult > 0) {
            showQueue();
            printf("-->%d:", dequeueResult);
            showResult(dequeueResult);
        } else {
            showResult(dequeueResult);
        }
    }
    for(i = 2;i >= 0;i--){
        showQueue();
        printf("<--%d:", i);
        showResult(enqueue(i));
    }
    return 0;
}