#include <stdio.h>
#include <stdlib.h>

double calc(int n,int m) {
int i,j,n0=1,n1=1;
double sum1=0,sum2=0;
for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            sum1 = sum1 + n1 + 1/(j+n1);
        }
sum2 = sum2 + i*sum1;
}
return sum2;
}


int main()
{ printf("%lf",calc(5,8));
    return 0;
}
