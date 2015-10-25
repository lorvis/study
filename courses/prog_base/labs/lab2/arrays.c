#include <stdio.h>
#include <stdlib.h>
void fillRand2(int arr[],int size)
{
    int i;
    for(i=0; i<=size-1; i++)
    {
        arr[i]=(rand()%256)*(-1+2*(rand()%2));
    }
    return;
}

int checkRand2(int arr[], int size)
{
    int i;
    for(i=0; i<=size-1; i++)
    {
        if(arr[i]<-255||arr[i]>255)
        {
            return 0;
        }
    }
    return 1;
}

float meanValue(int arr[], int size)
{
    int i,sum=0;
    for(i=0; i<=size-1; i++)
    {
        sum = sum + arr[i];
    }
    return sum/size;
}

int maxValue(int arr[], int size)
{
    int i,max;
    max = arr[0];
    for(i=1; i<=size-1; i++)
    {
        if(arr[i]>max)
        {
            max = arr[i];
        };

    };
    return max;
}

int meanIndex(int arr[], int size)
{
    int i,sum=0,minor,minorI;
    float norm;
    for(i=0; i<=size-1; i++)
    {
        sum = sum + arr[i];
    }
    norm = sum/size;
    minor = arr[0];
    minorI=0;
    for(i=1; i<=size-1; i++)
    {
        if(abs(norm-arr[i])<minor)
        {
            minor = arr[i];
            minorI=i;
        }

    }
    return minorI;
}
int maxOccurance(int arr[],int size)
{
    int i,j,max=-1073741824,co=-1073741824;
    for(i=0; i<=size-1; i++)
    {
    int coarray[2]={0,0};
        for(j=0; j<=size-1; j++)
        {
            if(arr[i]==arr[j])
            {
            coarray[1]=coarray[1]+1;
            coarray[2]=i;
            }
           if (coarray[1]>1) {
            co=arr[i];
            if(co>max){
                max=co;
            }
           }
        };
    };
    if (max!=-1073741824){
        return max;
    }
    return 0;
}

int diff(int arr1[], int arr2[], int res[], int size){
int i,dif=0,ress;
for(i=0;i<=size-1;i++) {
res[i]=arr1[i]-arr2[i];
}
for(i=0;i<=size-1;i++) {
    if(res[i]!=0){
        dif=dif+1;
    }
}
if (dif!=0){
    ress = 0;
    return ress;
}
ress = 1;
return ress;
}

void sub(int arr1[], int arr2[], int res[], int size) {
int i;
for(i=0;i<=size-1;i++) {
res[i]=arr1[i]-arr2[i];
}
}

int lt(int arr1[], int arr2[], int size) {
    int i;
    for(i=0;i<=size-1;i++) {
  if(arr1[i]>=arr2[2]) {
    return 0;
  }
  return 1;
}
}
void lor(int arr1[], int arr2[], int res[], int size){
    int i;
for(i=0;i<=size-1;i++) {
res[i]=(abs(arr1[i])%2)||(abs(arr2[i])%2);
}
}



int main()
{
    srand(time(NULL));
    int arr[10],i,arr1[10],arr2[10],res[10],result;
    int size = 10;
    fillRand2(arr,10);
    fillRand2(arr1,10);
    fillRand2(arr2,10);
    fillRand2(res,10);
    arr[1]=15;
    arr[2]=15;
    arr[3]=156;
    arr[4]=156;
   // for(i=0; i<=9; i++)
   // {
    //    printf("%i ",arr1[i]);}
    result = diff(arr1,arr2,res,10);
    printf("%i",result);
    return 0;
}

