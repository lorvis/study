#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double long2double(long long int thing)
{
double number=0;
double endnum;
int expo=0;
int sign=0;
int bit;
for(bit=51;bit>=0;bit--) {
long long int mask = (1ll << bit);
if ((mask&thing)>0) {
number= number + 1/pow(2,52-bit);
}
};
for(bit=52;bit<=62;bit++) {
long long int mask = (1ll << bit);
if ((mask&thing)>0) {
expo = expo + pow(2,bit-52);
int dif = pow(2,bit-52);
}
};
sign = pow(-1,(thing>>63));
    if (expo==2047&&number!=0) {
        return NAN;
    };
    if (expo==2047&&number==0) {
        return sign*INFINITY;
    }
    if (expo==0&&number==0) {
        if (sign==-1) {return -0;}
        if (sign==1) {return 0;}


    }
    if (expo==0&&number!=0) {
      endnum = sign*number*pow(2,-1022);
    return endnum;
    }
    int endexpo = expo - 1023;
    endnum = sign*(number+1)*pow(2,endexpo);
return endnum;
}


double main() {
double result = long2double(454);
printf("IN MAIN = %.325lf !!", result);
return 0;
}

