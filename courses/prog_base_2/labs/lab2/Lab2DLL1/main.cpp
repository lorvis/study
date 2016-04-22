#include <stdio.h>
#include "main.h"
#include "queue_t.h"

// a sample exported function

int DLL_EXPORT check(queue_t * to_check){
return queue_size(to_check) > 10;
}

void DLL_EXPORT action(queue_t * action_object){
puts("QUEUE SIZE IS OVER 10, REMOVING 5 ELEMENTS:");
int sum = 0;
for(int i = 0; i < 5 ; i++)
sum+= queue_remove(action_object);
printf("SUM: %i",sum);
puts(" ");
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
