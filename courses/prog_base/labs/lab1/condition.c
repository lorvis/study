#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int satisfies(int a, int b, int c) {
int modmin, sum2, max, min,result, sum;
if ((a<0)&&(b<0)&&(c<0)) {
    if ((a<b)&&(a<c)) {
        modmin = abs(a);
        sum2 = b+c;
    } else {
        if ((b<a)&&(b<c)) {
            modmin = abs(b);
            sum2 = a+c;
        } else { if ((c<b)&&(c<a))
            {modmin = abs(c);
            sum2 = a+b;};
        }
    }

 if (sum2<-256&&(modmin&(modmin-1)==0)&&modmin<256) {
        printf("--- \n");
        return 1;
} else {
if (((abs(sum2)-modmin)<16)||(abs(sum2)<16)) {
        printf("--- \n");
        return 1
;};};
}
if (a<0&&b>=0&&c>=0) {return (a>-256);};
if (a>=0&&b<0&&c>=0) {return (b>-256);};
if (a>=0&&b>=0&&c<0) {return (c>-256);};
if (a<0&&b<0&&c>=0) {return ((a+b)*2>-256);};
if (a>=0&&b<0&&c<0) {return ((b+c)*2>-256);};
if (a<0&&b>=0&&c<0) {return ((a+c)*2>-256);};

if (a>=0&&b>=0&&c>=0) {
if (a>b&&a>c) {max = a;
if (b<c) { min = b ;} else {min = c;};
} ;
if (b>c&&b>a) {max = b;
if (a<c) {min = a;} else {min = c;};
};
if (c>b&&c>a) {max = c;
if (a<b) {min = a;} else {min = b;};
};
if (min+max<256) {return 1;};
};
return 0;
}

int main()
{ int aval=-2100;int bval=22;int cval=23;
 int result = satisfies(aval,bval,cval);
    return result;
}
