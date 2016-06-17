#include <stdlib.h>
#include <windows.h>
#include "queue_t.h"

#define QUEUE_HEAD_ID 0
#define QUEUE_SIZE 4
#define NUMBER_RANGE 200

typedef int (*check_f)(queue_t *);
typedef void (*act_f)(queue_t *);

struct dynamic
{
    HANDLE Hlib;
    check_f check;
    act_f action;
};

typedef struct dynamic dynamic_t;

dynamic_t * dynamic_init(const char * dllName);


int main()
{
    srand(time(NULL));

    queue_t * q = queue_new(QUEUE_SIZE);
    for(int i = 0; i < QUEUE_SIZE; i++)
        queue_add(q,rand()%(NUMBER_RANGE*2)-NUMBER_RANGE);
    int choice = 0;
    while (choice!=1&&choice!=2){
    system("cls");
    puts("Choose your library, type 1 or 2");
    scanf("%i",&choice);
    }

    dynamic_t * dyn;

    if(choice==1){
    dyn = dynamic_init("Lab2DLL1.dll");
    if(dyn==NULL){
    puts("FAILED TO LOAD DLL1");
    exit(1);
    }
    }

    else{
    dyn = dynamic_init("Lab2DLL2.dll");
    if(dyn==NULL){
    puts("FAILED TO LOAD DLL2");
    exit(1);
    }
    }

    puts("ORIGINAL QUEUE:");
    queue_show(q);
    puts(" ");

    if(dyn->check(q))
        dyn->action(q);

    queue_show(q);

    queue_free(q);

    return 0;
}

dynamic_t * dynamic_init(const char * dllName)
{
    dynamic_t * newDyn = malloc(sizeof(dynamic_t));
    newDyn->Hlib = LoadLibrary(dllName);
    newDyn->action = NULL;
    newDyn->check = NULL;
    if (NULL != newDyn->Hlib)
    {
        newDyn->action = GetProcAddress(newDyn->Hlib,"action");
        newDyn->check = GetProcAddress(newDyn->Hlib,"check");
        return newDyn;
    }

    else
    {
        return NULL;
    }
}
