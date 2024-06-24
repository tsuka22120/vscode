#include <stdbool.h>
#include <stdio.h>
#define HEIGHT 5
#define TOWERS 3

typedef struct {
    int data[HEIGHT];
    int volume;
} Stack;

void init(Stack *stack) {
    int i;
    for (i = 0; i < HEIGHT; i++) {
        stack->data[i] = 0;  // スタックのすべての要素を0にする
    }
    stack->volume = 0;  // スタックに格納されているデータ数を0にする
}

int push(Stack *stack, int number) {
    if (stack->volume == HEIGHT) {  // これ以上スタックできないなら-1を返す
        return -1;
    }
    stack->data[stack->volume] = number;  // データを最上位に積み込む
    stack->volume++;                      // データの個数を増やす
    return 0;
}

int pop(Stack *stack) {
    int num;
    if (stack->volume == 0) {
        return -1;
    }
    stack->volume--;  // 格納されているデータ個数のカウントを減らす
    num = stack->data[stack->volume];  // 取り出すデータを取り出す
    stack->data[stack->volume] = 0;  // 取り出した場所を初期化する
    return num;
}

void printStack(Stack *stack) {
    int i;
    printf("[ ");
    for (i = 0; i < HEIGHT; i++) {  // スタックに格納されている値を
        printf("%d ", stack->data[i]);  // スタックされている順番に1行に表示
    }
    printf("]\n");
}

/// @brief 塔の最上位の値を返す関数
/// @param tower 塔の構造体
/// @return 塔の最上位の値
int top(Stack tower) {
    return tower.data[tower.volume - 1]; /* スタックの最上位の値を返す */
}

/// @brief 値を移動できるかどうかを判定する関数
/// @param fromTower 移動元の塔
/// @param toTower 移動先の塔
/// @return 可能なら1, 不可能なら0
int enableStack(Stack fromTower, Stack toTower) {
    if (fromTower.volume != 0 && toTower.volume != HEIGHT &&
        top(fromTower) < top(toTower)) {
        return 1; /* 移動可能である条件に応じて返り値を返す */
    } else {
        return 0;
    }
}

/// @brief クリアしているかどうかを判定する関数
/// @param tower 塔の構造体
/// @param blocks ブロックの数
/// @return クリアしているなら1, していないなら0
int checkFinish(Stack tower, int blocks) {
    int i;
    int check = blocks;
    for (i = 0; i < blocks; i++) {
        if (tower.data[i] == check--) {
        } else {
            return 0;
        }
    }
    return 1;
    // ブロックが初期状態と同じ状態かチェックする
}

int main(void) {
    int i;
    int count = 1;
    int fromNumber, toNumber;
    int tempNumber;
    int blocks;
    Stack tower[TOWERS];

    printf("Select the number of steps(3, 4, 5):");
    while (scanf("%d", &blocks) != 1 || blocks < 3 || blocks > 5) {
        while (getchar() != '\n');
        printf("error please rewrite\n");
        printf("Select the number of steps(3, 4, 5):");
    }
    /*3 塔を初期化する*/
    for (i = 0; i < TOWERS; i++) {
        init(&tower[i]);
    }
    /*第１塔に決められた個数をスタックする*/
    i = blocks;
    while (i != 0) {
        push(&tower[0], i--);
    }

    /*塔の初期状態を表示する*/
    for (i = 0; i < TOWERS; i++) {
        printf("%d:", i + 1);
        printStack(&tower[i]);
    }
    while (1) {
        // 今，何回目の移動であるかを数える．
        printf("%dth\n", count++);
        // 移動元と移動先を受け取る
        while (1) {
            printf("enter the source and destination towers.[? ?]:");
            while (scanf("%d%d", &fromNumber, &toNumber) != 2 || toNumber > 3 ||
                toNumber < 1 || fromNumber > 3 || fromNumber < 1) {
                while (getchar() != '\n');
                printf("error please rewrite\n");
                printf("enter the source and destination towers.[? ?]:");
            }
            // 移動元の塔から移動先の塔にデータを移動させる
            if (enableStack(tower[fromNumber - 1], tower[toNumber - 1]) == 1) {
                tower[toNumber - 1].data[tower[toNumber - 1].volume] =
                    pop(&tower[fromNumber - 1]);
                tower[toNumber - 1].volume++;
                break;
            } else {
                printf("Cannot move\n");
            }
        }
        // 現在の塔の状態を表示する
        for (i = 0; i < TOWERS; i++) {
            printf("%d:", i + 1);
            printStack(&tower[i]);
        }
        // クリア判定をする
        for (i = 1; i < TOWERS; i++) {
            if (checkFinish(tower[i], blocks) == 1) {
                printf("clear!\n");
                return 0;
            }
        }
    }
}