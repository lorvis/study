#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char word[100];
    int orderflag=0;
    int first=0;
    int last=0;
    scanf("%s",&word);
    printf("%i",digitfunc(word,first,last,orderflag));
    return 0;
}

int digitfunc(char* word,int first, int last,int orderflag){
if(isdigit(*word)){
switch(orderflag){
case 0:first=(int)(*word); orderflag++; break;
case 1:last=(int)(*word); break;
default: exit(EXIT_FAILURE); break;
}
}
if(*word=='\0'){
    return last+first;
} else {
return digitfunc(word+1,first,last,orderflag);
}
}
