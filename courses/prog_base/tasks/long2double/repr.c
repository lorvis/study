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
printf("Mantissa! \n");
for(bit=51;bit>=0;bit--) {
long long int mask = (1 << bit);
if ((mask&thing)>0) {
number= number + 1/pow(2,51-bit);
}
printf("bit = %i, number = %lf \n ",bit, number);
};
printf("Expo! \n");
for(bit=52;bit<=62;bit++) {
long long int mask = (1 << bit);
if ((mask&thing)>0) {
expo = expo + pow(2,bit-52);
int dif = pow(2,bit-52);
printf("difference = %i ",dif);
}
printf("bit = %i, expo = %i, \n ",bit, expo);
};
printf("Sign! \n");
if((1<<63)&(thing)>0) {
    sign=-1;
}else {
sign = 1;}
printf("sign = %i \n",sign);
    if (expo==2047&&number!=0) {
        printf("Expo 2047, Number!=0, NAN! \n");
        return NAN;
    };
    if (expo==2047&&number==0) {
        printf("Expo 2047, Number = 0, INFINITY \n");
        return sign*INFINITY;
    }
    if (expo==0&&number==0) {
        printf("Expo 0, Number 0 \n");
        if (sign==-1) {return -0;}
        if (sign==1) {return 0;}


    }
    if (expo==0&&number!=0) {
            printf("DENORMALIZED \n");
      endnum = sign*number*pow(2,-1022);
    printf("Endnum = %.325lf !!! \n",endnum);
    return endnum;
    }
    int endexpo = expo - 1023;
    printf("Number = %lf, Endexpo = %i, Sign = %i \n",number,endexpo,sign);
    endnum = sign*(number+1)*pow(2,endexpo);
    printf("Endnum IN FUNCTION = %.325lf !!! \n",endnum);
return endnum;
}


double main() {
double result = long2double(0);
printf("IN MAIN = %.325lf !!", result);
return 0;
}

