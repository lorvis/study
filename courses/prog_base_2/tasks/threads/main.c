#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "writer_reader.h"

int main()
{
    //creating variables for functions

    char  test_char = '7';
    char * test_string = "Using =)))) string!!";
    mutex_t * for_funcs = mutex_new();

    //creating arguments for callbacks

    //argument for writer callback function

    mutexedCallbackStringCharArgument test_args =
    {
        .wChar = &test_char,
        .wString = test_string,
        .mutex_arg = for_funcs,
    };

    //argument for reader callback function

    mutexedCallbackCharArgument test_reader_arg =
    {
        .some_char = &test_char,
        .mutex_arg = for_funcs,

    };

    //initializing threads

    writer_t test_writer = writer_new((mutexedCallbackStringCharArgument *)(&test_args));
    writer_t test_writer1 = writer_new((mutexedCallbackStringCharArgument *)(&test_args));
    writer_t test_writer2 = writer_new((mutexedCallbackStringCharArgument *)(&test_args));
    reader_t test_reader = reader_new((mutexedCallbackCharArgument *)&test_reader_arg);
    reader_t test_reader1 = reader_new((mutexedCallbackCharArgument *)&test_reader_arg);

    //letting threds work
    while(1);

    //don't think it will work
    reader_free(test_reader);
    reader_free(test_reader1);
    writer_free(test_writer);
    writer_free(test_writer1);
    writer_free(test_writer2);
    mutex_free(for_funcs);

    return 0;
}
