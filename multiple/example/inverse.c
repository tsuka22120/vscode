#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1.0e-8

double inverse2(double);

int main(int argc, char **argv)
{
    double a = 1234;
    double b;
    double r2;
    b = 1.0 / a;
    r2 = inverse2(a);
    printf("a = %5.16lf\n", a);
    printf("true 1/a = %5.16lf\n", b);
    printf("inverse2 = %5.16lf\n", r2);
    return 0;
}

double inverse2(double a)
{
    double x;
    double x0;
    double g;

    x = 0.2 * pow(10, -(double)((int)log10(a)));

    while(1){
        x0 = x;
        x = x0 * (2 - a * x0);
        g = fabs(x - x0);
        printf("g = %5.16lf\n", g);
        if(g <= eps){
            break;
        }
    }
    return x;
}