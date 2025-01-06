#include <stdio.h>
#include <math.h>

int bisection(double, double, double *);
double f(double);
int sgn(double);


int main(int argc, char **argv)
{
    double a, b;  //  適当な区間 [a, b]
    double x;     //  解
    int r;        //  戻り値


    a = 1.0;
    b = 4.0;
    r = bisection(a, b, &x);
    printf("x = %lf\n", x);
    printf("戻り値 = %d\n", r);

    return(0);
}


//
//  二分法で f(x) = 0 を解く
//  正常終了なら0を返す。
//  f(a)の符号とf(b)の符号が同じなら-1を返す。
//
int bisection(double a, double b, double *x)
{
    double e;        //  収束判定用の定数
    double d;        //  現在のxの値
    double fx;       //  f(x)の値
    int as, bs, cs;  //  f(a), f(b), f(x)の符号


    e = 1.e-7;
    as = sgn(f(a));  //  f(a)の符号
    bs = sgn(f(b));  //  f(b)の符号

    if (as == bs) return(-1);  //  error

    while (1)
    {
        d = (a + b) / 2.0;
        fx = f(d);
        cs = sgn(fx);
        if (cs == as) a = d;
        if (cs == bs) b = d;
        if (fx == 0.0) break;  //  収束
        if (fabs(a - b) < e) break;  //  区間が十分狭くなった
    }

    *x = d;
    return(0);
}


//  f(x)
double f(double x)
{
    return(x * x - 6.0);
}


//
//  符号関数
//
//  Input:
//    g ... 符号を調べる値
//
//  Output:
//    なし
//
//  Return:
//    -1 for g < 0
//    +1 for g > 0
//     0 for g = 0
//
int sgn(double g)
{
    if (g < 0.0) return(-1);
    if (g > 0.0) return( 1);
    return(0);
}
