#include <stdio.h>
#include <stdlib.h>

void fillRand(int mat[4][4])
{
    int i;
    int j;
    for(i=0;i<=3;i++) {
        for(j=0;j<=3;j++) {
            mat[i][j]=(rand()%999)*(-1+2*(rand()%2));
        }
    }

}

void flipV(int mat[4][4]) {
int mat2[4][4];
int i,j,i2;
for(i=0;i<=3;i++) {
switch(i) {
case 0:i2=3; break;
case 1:i2=1; break;
case 2:i2=-1; break;
case 3:i2=-3; break;
}
for(j=0;j<=3;j++) {
    mat2[i][j]=mat[i+i2][j];
}

}
mat=mat2;
}


void rotateCW180(int mat[4][4])
{
    int n,m11,m112;
    int i,j;
    for(n=1; n<=2; n++)
    {
        m11=mat[0][0];

        for(i=0; i<=2; i++)
        {
            mat[i][0]=mat[i+1][0];
        };
        for(i=0; i<=2; i++)
        {
            mat[3][i]=mat[3][i+1];
        };
        for(i=3; i>0; i--)
        {
            mat[i][3]=mat[i-1][3];
        };
        m112=mat[0][0];
        mat[0][0]=m11;
        for(i=3; i>0; i--)
        {
            mat[0][i]=mat[0][i-1];
        };
        mat[0][0]=m112;
        m11=mat[1][1];
        mat[1][1]=mat[2][1];
        mat[2][1]=mat[2][2];
        mat[2][2]=mat[1][2];
        mat[1][2]=m11;
    };
    for(i=0; i<=3; i++)
    {
        for (j=0; j<=3; j++)
       {
            printf("%5i ",mat[i][j]);
       };
        printf("\n");
}
return mat;
}
