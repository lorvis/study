#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 double calc(double x, double y, double z)
{   int n0=1;
    int n1=1;
    if ((n0+1)*abs(x+y)==0) {return NAN;};
    if (z==0) {return NAN;};
    if ((y-x)==0) {return NAN;};
    if ((y-x)<0&&((1/z)-(int)(1/z))!=0) {return NAN;};
    if (sin(y)<0&&((cos(x)/z + abs(x-y))-(int)(cos(x)/z + abs(x-y)))!=0) {return NAN;};
    if (x<0&&((y+1)-(int)(y+1))!=0) {return NAN;};
    double a1 = (y/(n0+1)*abs(x+y));
    double a2 = (n1+pow(sin(y),(cos(x)/z + abs(x-y))));
    double a0 = (pow(x,(y+1))/pow((y-x),(1/z)));
    double a = a0 + a1 + a2;
    return a;
}

double main()
{
    double x;
    double y;
    double z;
    printf("Enter x = ");
    scanf("%lf",&x);
    printf("Enter y = ");
    scanf("%lf",&y);
    printf("Enter z = ");
    scanf("%lf",&z);
    double r=calc(x,y,z);
    printf("%lf",r);
    return 0;
}
