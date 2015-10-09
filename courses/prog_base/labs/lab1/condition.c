#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int satisfies(int a, int b, int c) {
int modmin, sum2, max, min,result, sum;
if (a<0&&b<0&&c<0) {
    if (a<b&&a<c) {
        modmin = abs(a);
        sum2 = b+c;
    } else {
        if (b<a&&b<c) {
            modmin = abs(b);
            sum2 = a+c;
        } else { if (c<b&&c<a)
            {modmin = abs(c);
            sum2 = a+b;};
        }
    }
};
 if (sum2<-256&&(modmin&(modmin-1)==0)&&modmin<256) {
        return 1;
} else {
if ((abs(sum2)>16)||(modmin>8)) {
    return 1;
} else {
if (a<0&&b>0&&c>0) {return (a>-256);};
if (a>0&&b<0&&c>0) {return (b>-256);};
if (a<0&&b>0&&c<0) {return (c>-256);};
if (a<0&&b<0&&c>0) {return ((a+b)*2>-256);};
if (a>0&&b<0&&c<0) {return ((b+c)*2>-256);};
if (a<0&&b>0&&c<0) {return ((a+c)*2>-256);};
}
{
    if (sum2<0||modmin<0){
        if ((sum2<0&&modmin>=0)) {
                result=(sum2>-256);
         if (result==1) {return result;};

         } else {
         if (sum>=0&&modmin<0) {
            result=(modmin>-256);
            if (result==1) {return result;};
         } else {
         result = ((sum2+modmin)*(22)>-256);
         if (result==1) {return result;};
         }
         }
    }
}
}
if (a>0&&b>0&&c>0) {if (a>0&&b>0&&c>0) {
if (a>b&&a>c) {max = a;};
if (b>a&&b>c) {max = b;};
if (c>b&&c>a) {max = c;};
if (log(32768)/log(max) <= min) {return 1;};
};
if (result==1) {return result;} else {return 0;};
}
}

int main()
{ int aval=2;int bval=3;int cval=5;
 int result = satisfies(aval,bval,cval);
    return result;
}
