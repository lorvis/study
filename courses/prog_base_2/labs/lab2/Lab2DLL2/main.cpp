#include <stdio.h>
#include "main.h"
#include "queue_t.h"

// a sample exported function

int DLL_EXPORT check(queue_t * to_check){
    int sum = 0;

    for(int i = 0 ; i < queue_size(to_check); i++){
        sum+=queue_get(to_check,i);
    }
    printf("SUM AT CHECK IS %i\n", sum);
return sum > 100;
}

void DLL_EXPORT action(queue_t * action_object){
    puts("IT'S OVER 50!");
int sum = 100;
while(sum>=50&&queue_size(action_object)>0){
    sum=0;
    queue_remove(action_object);
    for(int i = 0; i < queue_size(action_object); i++)
    sum+=queue_get(action_object,i);
}
printf("SUM AFTER REMOVING %i\n", sum);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
