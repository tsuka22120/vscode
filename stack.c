#include<stdio.h>
#include<stdbool.h>
#define HEIGHT 5

typedef struct{
  int data[HEIGHT];
  int volume;
}Stack;

void init(Stack* stack) {
  int i;
  for (i = 0; i < HEIGHT; i++) {
    stack->data[i] = 0; //スタックのすべての要素を0にする
  }
  stack->volume = 0; //スタックに格納されているデータ数を0にする
}

int push(Stack* stack, int number) {
  if (stack->volume == HEIGHT) { //これ以上スタックできないなら-1を返す
    return -1;
  }
  stack->data[stack->volume] = number; //データを最上位に積み込む
  stack->volume++; //データの個数を増やす
  return 0;
}

int pop(Stack* stack) {
  int num;
  if (stack->volume == 0) {
    return -1;
  }
  stack->volume--; //格納されているデータ個数のカウントを減らす
  num = stack->data[stack->volume]; //取り出すデータを取り出す
  stack->data[stack->volume] = 0; //取り出した場所を初期化する
  return num;
}

void printStack(Stack* stack) {
  int i;
  printf("[ ");
  for (i = 0; i < HEIGHT; i++) { //スタックに格納されている値を
    printf("%d ", stack->data[i]); //スタックされている順番に1行に表示
  }
  printf("]\n");
}

bool puthTest(Stack stack) {
  if (stack.volume == HEIGHT) {
    return false;
  }
  else {
    return true;
  }
}

bool popTest(Stack stack) {
  if (stack.volume == 0) {
    return false;
  }
  else {
    return true;
  }
}

int main(void) {
  Stack stack;
  int i, check;
  init(&stack);
  printf("スタックの最大値:%d\n", HEIGHT);
  for (i = 10; i < 40; i += 10) {
    if (puthTest(stack) == true) {
      printf("pushed %d\n", i);
      push(&stack, i);
    }
    else {
      printf("error\n");
    }
  }

  printf("データ順にスタックされているか\n");
  printStack(&stack);

  printf("データ順に取り出せているか\n");
  for (i = 0; i < 3; i++) {
    if (popTest(stack) == true) {
      printf("poped %d\n", stack.data[stack.volume - 1]);
      pop(&stack);
    }
    else {
      printf("空の時にデータを取り出そうとしたときにどのような動作をするか\n");
      printf("error\n");
    }
  }

  for (i = 10; i < 70; i += 10) {
    if (puthTest(stack) == true) {
      printf("pushed %d\n", i);
      push(&stack, i);
    }
    else {
      printf("満杯の時にデータを追加しようとしたときにどのような動作をするか\n");
      printf("error\n");
    }
  }
  return 0;
}