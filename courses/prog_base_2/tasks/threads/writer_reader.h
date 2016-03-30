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

struct mut_string_pt_with_char_pt_arg{
mutex_t * mutex_arg;
char* wString;
char* wChar;
};

struct mut_two_char_pt_arg{
mutex_t * mutex_arg;
char * first_char_pt_arg;
char * second_char_pt_arg;
};

struct mut_char_pt{
mutex_t * mutex_arg;
char * some_char;
};

typedef struct mut_char_pt mut_char_pt;
typedef struct mut_string_pt_with_char_pt_arg mut_string_pt_with_char_pt_arg;
typedef struct mut_two_char_pt_arg mut_two_char_pt_arg;

writer_t  writer_new(mut_string_pt_with_char_pt_arg * input);
void writer_free(writer_t to_free);

#endif // WRITER_READER_HEADER_INCLUDED
