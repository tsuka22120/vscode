#include <stdbool.h>
#include <stdio.h>
#define HEIGHT 5

typedef struct {
    int data[HEIGHT];
    int volume;
} Stack;

/// @brief 構造体を初期化する
/// @param stack 初期化する構造体
void init(Stack *stack) {
    int i;
    for (i = 0; i < HEIGHT; i++) {
        stack->data[i] = 0;  // スタックのすべての要素を0にする
    }
    stack->volume = 0;  // スタックに格納されているデータ数を0にする
}

/// @brief 構造体にデータをpushする
/// @param stack pushする構造体
/// @param number pushするデータ
/// @return 成功したら0, 失敗したら-1
int push(Stack *stack, int number) {
    if (stack->volume == HEIGHT) {  // これ以上スタックできないなら-1を返す
        return -1;
    }
    stack->data[stack->volume] = number;  // データを最上位に積み込む
    stack->volume++;                      // データの個数を増やす
    return 0;
}

/// @brief 構造体からデータをpopする
/// @param stack popする構造体
/// @return 成功したらpopしたデータ, 失敗したら-1
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

/// @brief 構造体に格納されているデータを表示する
/// @param stack 表示する構造体
void printStack(Stack *stack) {
    int i;
    printf("[ ");
    for (i = 0; i < stack->volume; i++) {  // スタックに格納されている値を
        printf("%d ", stack->data[i]);  // スタックされている順番に1行に表示
    }
    printf("]\n");
}

/// @brief pushできるかどうかを判定する
/// @param stack 判定する構造体
/// @return pushできるならtrue, できないならfalse
bool pushTest(Stack stack) {
    if (stack.volume == HEIGHT) {
        return false;
    } else {
        return true;
    }
}

/// @brief popできるかどうかを判定する
/// @param stack 判定する構造体
/// @return popできるならtrue, できないならfalse
bool popTest(Stack stack) {
    if (stack.volume == 0) {
        return false;
    } else {
        return true;
    }
}

int main(void) {
    Stack stack;
    int i, check;
    init(&stack);
    printf("MAX STACK NUM:%d\n", HEIGHT);
    for (i = 10; i < 40; i += 10) {
        if (pushTest(stack) == true) {
            printf("pushed %d\n", i);
            push(&stack, i);
        } else {
            printf("error\n");
        }
    }

    printf("The data is stacked in order?\n");
    printStack(&stack);

    printf("The data is retrieved in order?\n");
    for (i = 0; i < 4; i++) {
        if (popTest(stack) == true) {
            printf("popped %d\n", pop(&stack));
        } else {
            printf(
                "What happens when you try to retrieve data when it is empty"
                "\n");
            printf("error\n");
        }
    }

    for (i = 10; i < 70; i += 10) {
        if (pushTest(stack) == true) {
            printf("pushed %d\n", i);
            push(&stack, i);
        } else {
            printf(
                "What happens when you try to add data when it is full"
                "\n");
            printf("error\n");
        }
    }
    return 0;
}