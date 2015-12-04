#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * i = malloc(4);
    int * j = malloc(4);
    int * count = malloc(4);
    *i = 0;
    *j = 0;
    *count = 0;
    char arr[] = "ora-ora-ora-ora-ora";
    char * consonants = malloc(21);
    consonants = "bvdfghjklmnpqrstvxzwy";
    char * consocyc = malloc(21);
    consocyc = consonants;
    char * word = malloc(40);
    scanf("%s",word);
    while(*word!='\0'){
    while(*consocyc!='\0'){
    if(*word==*consocyc){*count=*count+1;}
    consocyc++;
    }
    word++;
    consocyc=consonants;
    }
    free(consonants);
    free(word);
    free(consocyc);
    free(i);
    free(j);
    free(count);
    return *count;
}
