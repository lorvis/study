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
        } else {
            modmin = abs(c);
            sum2 = a+b;
        }
    }
};
if (sum2<-256&&(modmin&(modmin-1)==0)&&modmin<256) {
        result = 1; return result;
} else {
if (abs(sum2)>16||modmin>8) {
    result = 1; return result;

} else {
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
 {
if (sum2>=0&&modmin>=0) {
if (sum2>modmin) {max = sum2; min = modmin;} else {max = modmin; min = sum2;};
result = ((log(32768)/log(max))<=min);
};
}
if (result==1) {return result;} else {return 0;};

}

int main()
{
    printf("Hello world!\n");
    return 0;
}
