#include "writer_reader.h"
#include <ctype.h>

//THREAD VARIABLE ACCESS FUNCTION

typedef void (*voidfunc)(void * arg);

static void mutexed_void_variable_access(void * variable_pt, voidfunc access_with, mutex_t * for_access){
mutex_lock(for_access);
access_with(variable_pt);
mutex_unlock(for_access);
}


//READER

static void reader_core(void * some_char){
if(ispunct(*(char *)some_char))
putchar(*(char *)some_char);
}

static void reader(mut_char_pt * reader_args){
voidfunc use_it_for_life = reader_core;
while(1){
mutexed_void_variable_access((void *)reader_args->some_char,use_it_for_life,reader_args->mutex_arg);
}
return;
}

reader_t reader_new(void * input){
return thread_create_args(reader,input);
}

void reader_free(reader_t to_free){
thread_free(to_free);
return;
}


//WRITER
typedef struct mut_string_pt_with_char_pt_arg mut_string_pt_with_char_pt_arg;

static void writer_core(mut_two_char_pt_arg * second_into_first){
*(second_into_first->first_char_pt_arg) = *(second_into_first->second_char_pt_arg);
}

static void writer(mut_string_pt_with_char_pt_arg * args){
char * IString = args->wString;
//char * IChar = ((string_pt_with_char_pt_arg *)args)->wChar;
mut_two_char_pt_arg * core_args = malloc(sizeof(mut_two_char_pt_arg));
core_args->first_char_pt_arg = malloc(sizeof(char *));
core_args->second_char_pt_arg = malloc(sizeof(char *));
core_args->first_char_pt_arg = args->wChar;
int length=0;
int pos=0;
while(IString[length]!='\0')
++length;
voidfunc writer_core_voidfunc = writer_core;
while(length){
(*core_args->second_char_pt_arg) = IString[length-1-((length+pos)%(length))];
mutexed_void_variable_access(core_args,writer_core_voidfunc,args->mutex_arg);
pos++;
}
free(core_args); //useless, i think . . .
free(core_args->first_char_pt_arg);
free(core_args->second_char_pt_arg);
puts((char *)"WRITER'S STRING LENGTH IS 0");
return;
}

writer_t writer_new(mut_string_pt_with_char_pt_arg * input){
return thread_create_args(writer,(void *)input);
}

void writer_free(writer_t to_free){
thread_free(to_free);
return;
}
