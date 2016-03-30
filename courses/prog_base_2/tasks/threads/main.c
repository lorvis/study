#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "writer_reader.h"

int main()
{
    char  test_char = '7';
    char * test_string = "Using =)))) string";
    mutex_t * for_funcs = mutex_new();

    mut_string_pt_with_char_pt_arg test_args = {
    .wChar = &test_char,
    .wString = test_string,
    .mutex_arg = for_funcs
    };

    mut_char_pt test_reader_arg = {
    .mutex_arg = for_funcs,
    .some_char = &test_char
    };

    writer_t test_writer = writer_new((mut_string_pt_with_char_pt_arg *)(&test_args));
    writer_t test_writer1 = writer_new((mut_string_pt_with_char_pt_arg *)(&test_args));
    writer_t test_writer2 = writer_new((mut_string_pt_with_char_pt_arg *)(&test_args));
    reader_t test_reader = reader_new((mut_char_pt *)&test_reader_arg);
    reader_t test_reader1 = reader_new((mut_char_pt *)&test_reader_arg);
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
