#include <stdio.h>
#include <math.h>

double newton(double);
double f(double);
double fdash(double);


int main(int argc, char **argv)
{
    double x;
    double x0;
    int i;


    for (i = -5 ; i <= 5 ; i++)
    {
        x0 = (double)i;
        x = newton(x0);
        printf("x0=%10.6lf,  x=%10.6lf\n", x0, x);  //  初期値x0と答えx
    }

    return(0);
}


//
//  Newton-Raphson法で f(x)=0 を解く (x0=初期値)
//
double newton(double x0)
{
    double x;  //  現在の近似値
    double b;  //  1つ前のx
    double e;  //  収束判定用


    e = 1.e-7;
    x = x0;
    b = x0;

    while (1)
    {
        b = x;  //  1つ前のx
        x = b - (f(b) / fdash(b));  //  0除算に注意
        // printf("x=%10.6lf\n", x);  //  現在の近似値
        if (fabs(x - b) < e) break;  //  収束
    }

    return(x);
}


//  f(x)
double f(double x)
{
    return(x * x + 4.0 * x + 5.0);//  ここに関数f(x)を書く
}


//  f'(x)
double fdash(double x)
{
    return(2 * x + 4.0);//  ここに関数f'(x)を書く
}
