#include "writer_reader.h"
#include <ctype.h>

//type of callback function for synchronized code piece

typedef void (*voidfunc)(void * arg);

//synchronized code piece, for_access - mutexed callback function
static void mutexed_void_variable_access(void * variable_pt, voidfunc access_with, mutex_t * for_access)
{
    mutex_lock(for_access);
    access_with(variable_pt);
    mutex_unlock(for_access);
}


//READER

//code piece which must be synchronized, it puts char if it's punctuation symbol
static void reader_core(void * some_char)
{
    if(ispunct(*(char *)some_char))
        putchar(*(char *)some_char);
}

//general writer thread function with cycled mutexed part
static void reader(mutexedCallbackCharArgument * reader_args)
{
    //initializing reader callback func
    voidfunc use_it_for_life = reader_core;
    //cycled calling a synchronized part of code with reader callback func
    while(1)
    {
        mutexed_void_variable_access((void *)reader_args->some_char,use_it_for_life,reader_args->mutex_arg);
    }
    return;
}

//constructor

reader_t reader_new(void * input)
{
    return thread_create_args(reader,input);
}

//destructor

void reader_free(reader_t to_free)
{
    thread_free(to_free);
    return;
}


//WRITER
typedef struct mutexedCallbackStringCharArgument mutexedCallbackStringCharArgument;

//code piece which must be synchronized it's copying value from second char (writer's string) to second (generic char)

static void writer_core(argsForWriter * second_into_first)
{
    *(second_into_first->first_char_pt_arg) = *(second_into_first->second_char_pt_arg);
}



static void writer(mutexedCallbackStringCharArgument * args)
{
    char * IString = args->wString;
    //allocating memory for writer callback func args
    argsForWriter * cbArgs = malloc(sizeof(argsForWriter));
    cbArgs->first_char_pt_arg = malloc(sizeof(char *));
    cbArgs->second_char_pt_arg = malloc(sizeof(char *));
    //first char of arg is always generic char
    cbArgs->first_char_pt_arg = args->wChar;
    int length=0;
    int pos=0;
    //initializing writer callback func
    voidfunc writer_core_voidfunc = writer_core;
    //works if strlen != 0
    while(strlen(IString))
    {
        //cycled going backward in the string
        (*cbArgs->second_char_pt_arg) = IString[strlen(IString)-1-((strlen(IString)+pos)%(strlen(IString)))];
        pos++;
        //performs a synchronized code
        mutexed_void_variable_access(cbArgs,writer_core_voidfunc,args->mutex_arg);

    }

    //useless, i think . . .
    free(cbArgs);
    free(cbArgs->first_char_pt_arg);
    free(cbArgs->second_char_pt_arg);
    puts((char *)"WRITER'S STRING LENGTH IS 0");
    return;
}

//constructor

writer_t writer_new(mutexedCallbackStringCharArgument * input)
{
    return thread_create_args(writer,(void *)input);
}

//destructor

void writer_free(writer_t to_free)
{
    thread_free(to_free);
    return;
}
