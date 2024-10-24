#include<stdio.h>

void char2bit(unsigned char,char *);

int main(void){
    unsigned int num[10];
    char bit[9];
    printf("文字を入力してください:");
    scanf("%d%d%d%d",num);
    char2bit(num,bit);
    printf("文字%cのビット列は%sです。\n",c,bit);
    return 0;
}

void char2bit(unsigned int num[],char *bit){
    int i;
    
}