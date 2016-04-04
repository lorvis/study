#ifndef WRITER_READER_HEADER_INCLUDED
#define WRITER_READER_HEADER_INCLUDED


#include <windows.h>
#include <stdio.h>
#include "mutex.h"
#include "thread.h"

typedef thread_t * reader_t;

void reader_free(reader_t to_free);
reader_t reader_new(void * input);


typedef thread_t * writer_t;

//String, char and mutex as writer's args

struct mutexedCallbackStringCharArgument{
mutex_t * mutex_arg;
char* wString;
char* wChar;
};

//args for writer's callback

struct argsForWriter{
mutex_t * mutex_arg;
char * first_char_pt_arg;
char * second_char_pt_arg;
};

//char and mutex as reader's args

struct mutexedCallbackCharArgument{
mutex_t * mutex_arg;
char * some_char;
};

typedef struct mutexedCallbackCharArgument mutexedCallbackCharArgument; //
typedef struct mutexedCallbackStringCharArgument mutexedCallbackStringCharArgument;
typedef struct argsForWriter argsForWriter;

writer_t  writer_new(mutexedCallbackStringCharArgument * input);
void writer_free(writer_t to_free);
reader_t reader_new(void * input);
void reader_free(reader_t to_free);

#endif // WRITER_READER_HEADER_INCLUDED
