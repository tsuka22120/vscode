#include <stdio.h>
#include <math.h>

int newton(int);
int f(int);
int fdash(int);


int main(int argc, char **argv)
{
    int x;
    int x0;
    int i;


    for (i = -5 ; i <= 5 ; i++)
    {
        x0 = i;
        x = newton(x0);
        printf("x0=%d,  x=%d\n", x0, x);  //  初期値x0と答えx
    }

    return(0);
}


//
//  Newton-Raphson法で f(x)=0 を解く (x0=初期値)
//
int newton(int x0)
{
    int x;  //  現在の近似値
    int b;  //  1つ前のx
    int e;  //  収束判定用


    e = 0;
    x = x0;
    b = x0;

    while (1)
    {
        b = x;  //  1つ前のx
        x = b - (f(b) / fdash(b));  //  0除算に注意
        printf("x=%d\n", x);  //  現在の近似値
        if (fabs(x - b)  ==  e) break;  //  収束
    }

    return(x);
}


//  f(x)
int f(int x)
{
    return(x * x * x - 9.0 * x);//  ここに関数f(x)を書く
}


//  f'(x)
int fdash(int x)
{
    return(3 * x  * x - 9.0);//  ここに関数f'(x)を書く
}
