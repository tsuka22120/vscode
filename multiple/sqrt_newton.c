#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int sqrt_newton(int);


int main(int argc, char **argv)
{
    int i, r, r1, r2, d;


    srandom(time(NULL));

    for (i = 0 ; i < 10 ; i++)
    {
        r = random();
        r1 = sqrt_newton(r);        //  自家製ルーチンで計算したもの
        r2 = (int)sqrt((double)r);  //  sqrt()で計算した平方根の整数部分
        d = r1 - r2;
        printf("%10d : %6d - %6d = %d\n", r, r1, r2, d);  //  r=10^{10}程度の値の平方根だから6桁あればOK
    }

    return(0);
}


//
//  平方根 (Newton-Raphson法)
//
//  入力:
//    N ... 平方根を求めたい整数
//
//  出力:
//    なし
//
//  戻り値:
//    -1 ... エラー(N<0の場合)
//    それ以外 ... \sqrt{N}を越えない最大の整数値
//
int sqrt_newton(int N)
{
    int x;  //  現在の平方根の近似値
    int b;  //  1つ前のx
    int c;  //  2つ前のx


    if (N < 0) return(-1);  //  N<0 ならエラーで-1を返す
    if ((N == 0) || (N == 1)) return(N);  //  N=0 or 1なら \sqrt{N}=N

    x = N / 2;
    b = x;
    c = x;

    while (1)
    {
        c = b;  //  2つ前のx
        b = x;  //  1つ前のx
        x = (b + (N / b)) / 2;  // x_{i+1}=(x_{i}+(N/x_{i}))/2

        if (x == b) break;  //  収束
        if (x == c)         //  振動
        {
            if (b < x) x = b;  //  小さい方をとる
            break;
        }
    }

    return(x);
}
