#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct startup {
    int invest;
    int age;
    char* name;
    int index;
    };

typedef struct startup startup;

int count(int size, startup stup[size]){
    int i;
    int counter=0;
for(i=0;i<size;i++){
    if(stup[i].invest>3000000){
    counter++;
    }
}
return counter;
}

void change(startup * pvar, const char * newValue){
pvar->name = newValue;
return;
}

void printing(struct startup * pvar){
        printf("Index - %i \n",pvar->index);
        printf("Name - %s \n",pvar->name);
        printf("Investment - %i \n",pvar->invest);
        printf("Age - %i \n",pvar->age);
        puts("\n");
}

int main()
{
    int index = -1;
    startup * pvar;
    char* operation[10];
    char* colist[] = {
    "counting",
    "change",
    "print",
    "quit"
    };
    int size = 15;
    int todo;
    enum {counting,changing,print,quit};
    srand(time(NULL));
    char* names[] = {
    "Random",
    "ABC",
    "Crying cats",
    "SUPER",
    "KP-52",
    "India",
    "Brains",
    "Network",
    "Water",
    "Fire",
    "Pizza",
    "Boomer",
    "Pong",
    "King-Kong",
    "Butterfly"
    };
    int i,j;
    startup stup[15];
    puts("Startups:\n\n\n");
    for(i=0;i<15;i++){
        stup[i].invest=i*rand()*20 + 100000;
    }
    for(i=0;i<size;i++){
        stup[i].age= 1 + rand()%5;
    }
    for(i=0;i<size;i++){
        stup[i].name = names[i];
    }
    for(i=0;i<size;i++){
        stup[i].index = i;
    }
    for(i=0;i<size;i++){
        printf("Index - %i \n",stup[i].index);
        printf("Name - %s \n",stup[i].name);
        printf("Investment - %i \n",stup[i].invest);
        printf("Age - %i \n",stup[i].age);
        puts("\n");
    }
puts("\n counting - function 1 \n change - function 2 \n print - to print \n quit - to quit");
do{
    scanf("%s",&operation);
    for(i=0;i<4;i++){
    if(strcmp(operation,colist[i])==0){
        todo=i;
        break;
    }
    }

switch(todo){
case counting: printf("\n Amount of startups with 3kk+ investemts = %i \n",count(size,stup)); break;
case changing:
    puts("Enter index of startup you want to change");
    scanf("%i",&index);
    pvar = &stup[index];
    change(pvar,"IT'S CHANGEDDD!!!!111");
    break;
case print:
    printing(pvar); break;
case quit: return 0;
default: break;
}
}while(1);
    return 0;
}
