#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>

#include "set.h"

// unit-test function
static void new_int_set_t_pt(void **state)
{
    set_t * test_set = NULL;
    test_set = set_new(10);
    assert_false(test_set == NULL);
    set_delete(test_set);
}

static void add_range_void_set_t_and_2_int_edges(void **state)
{
   set_t * test_set = set_new(10);
   set_add_range(test_set,0,4);
   int i;
   for(i = 0;i<5;i++){
    assert_int_equal(1,set_get_element(test_set,i));
   }
   for(i = 5;i<10;i++){
    assert_int_equal(0,set_get_element(test_set,i));
   }
   set_delete(test_set);
}
static void delete_range_void_set_t_and_2_int_edges(void **state)
{
set_t * test_set = set_new(10);
   set_add_range(test_set,0,9);
   set_delete_range(test_set,0,5);
   int i;
   for(i=0;i<5;i++){
    assert_int_equal(0,set_get_element(test_set,i));
   }
   for(i=6;i<10;i++){
    assert_int_equal(1,set_get_element(test_set,i));
   }
   set_delete(test_set);
}

static void absolute_complement_set_t_pt_out_2_set_t_pt_and_const_char_in(void **state)
{
set_t * test_set_A = set_new(10);
set_t * test_set_B = set_new(10);
set_t * test_set_C = set_new(10);
set_add_range(test_set_A,0,7);
set_add_range(test_set_B,5,9);
test_set_C = set_absolute_complement(test_set_A,test_set_B,"none");
int i;
   for(i=0;i<5;i++){
    assert_int_equal(1,set_get_element(test_set_C,i));
   }
   for(i=5;i<8;i++){
    assert_int_equal(0,set_get_element(test_set_C,i));
   }
   for(i=8;i<10;i++){
    assert_int_equal(1,set_get_element(test_set_C,i));
   }
set_delete(test_set_A);
set_delete(test_set_B);
set_delete(test_set_C);
}

static void relative_complement_set_t_pt_out_2_set_t_pt_and_const_char_in(void **state)
{
set_t * test_set_A = set_new(10);
set_t * test_set_B = set_new(10);
set_t * test_set_C = set_new(10);
set_add_range(test_set_A,0,7);
set_add_range(test_set_B,5,9);
test_set_C = set_relative_complement(test_set_A,test_set_B,"none");
int i;
   for(i=0;i<5;i++){
    assert_int_equal(1,set_get_element(test_set_C,i));
   }
   for(i=5;i<10;i++){
    assert_int_equal(0,set_get_element(test_set_C,i));
   }
set_delete(test_set_A);
set_delete(test_set_B);
set_delete(test_set_C);
}

static void merge_set_t_pt_out_2_set_t_pt_and_const_char_in(void **state)
{
set_t * test_set_A = set_new(10);
set_t * test_set_B = set_new(10);
set_t * test_set_C = set_new(10);
set_add_range(test_set_A,0,3);
set_add_range(test_set_B,4,7);
test_set_C = set_merge(test_set_A,test_set_B,"none");
int i;
   for(i=0;i<8;i++){
    assert_int_equal(1,set_get_element(test_set_C,i));
   }
   for(i=8;i<10;i++){
    assert_int_equal(0,set_get_element(test_set_C,i));
   }
set_delete(test_set_A);
set_delete(test_set_B);
set_delete(test_set_C);
}

static void intersection_set_t_pt_out_2_set_t_pt_and_const_char_in(void **state)
{
set_t * test_set_A = set_new(10);
set_t * test_set_B = set_new(10);
set_t * test_set_C = set_new(10);
set_add_range(test_set_A,0,7);
set_add_range(test_set_B,5,9);
test_set_C = _set_intersection(test_set_A,test_set_B,"none");
int i;
   for(i=0;i<5;i++){
    assert_int_equal(0,set_get_element(test_set_C,i));
   }
   for(i=5;i<8;i++){
    assert_int_equal(1,set_get_element(test_set_C,i));
   }
   for(i=8;i<10;i++){
    assert_int_equal(0,set_get_element(test_set_C,i));
   }
set_delete(test_set_A);
set_delete(test_set_B);
set_delete(test_set_C);
}

static void measure_power_int_set_t_pt(void **state)
{
set_t * test_set_A = set_new(10);
int i,test_count = 0;
set_add_range(test_set_A,0,5);
   for(i=0;i<10;i++){
    if(set_get_element(test_set_A,i)){
            test_count++;
    }
   }
assert_int_equal(6,test_count);
set_delete(test_set_A);
}

static void print_size_int_set_t_pt(void **state)
{
    set_t * test_set_A = set_new(10);
    assert_int_equal(10,set_print_size(test_set_A));
    set_delete(test_set_A);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_int_set_t_pt),
        cmocka_unit_test(add_range_void_set_t_and_2_int_edges),
        cmocka_unit_test(delete_range_void_set_t_and_2_int_edges),
        cmocka_unit_test(absolute_complement_set_t_pt_out_2_set_t_pt_and_const_char_in),
        cmocka_unit_test(relative_complement_set_t_pt_out_2_set_t_pt_and_const_char_in),
        cmocka_unit_test(merge_set_t_pt_out_2_set_t_pt_and_const_char_in),
        cmocka_unit_test(intersection_set_t_pt_out_2_set_t_pt_and_const_char_in),
        cmocka_unit_test(measure_power_int_set_t_pt),
        cmocka_unit_test(print_size_int_set_t_pt),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
