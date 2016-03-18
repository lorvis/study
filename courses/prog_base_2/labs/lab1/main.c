#include "heap.h"
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>

 static void heap_new__heap_t_pt__int_max_proc_and_free_memory(void **state)
{
heap_t * test_heap = NULL;
test_heap = heap_new(10,1000);
for(int i = 0;i<10;i++){
    assert_null(heap_get_proc(test_heap,i));
}
assert_non_null(test_heap);
heap_free(test_heap);
}

 static void heap_change_proc__int_error__heap_t_pt_int_mem_amount_and_void_pt_entity(void **state)
{
int test_ints[25];
for(int i = 0;i<25;i++){
test_ints[i] = i;
}
int index;
void * test_void = test_ints;
heap_t * test_heap = heap_new(10,1000);
index = heap_new_proc(test_heap,sizeof(test_ints),test_void);
assert_int_not_equal(index,-1);
assert_int_equal(heap_get_free_mem(test_heap),1000-sizeof(test_ints));
int * test_ints_2 = heap_get_proc_entity(test_heap,index);
for(int i = 0;i<25;i++)
assert_int_equal(i,test_ints_2[i]);
char test_word[6] = "HELLO!";
void * test_void_2 = test_word;
heap_change_proc(test_heap,0,sizeof(test_word),test_void_2);
assert_int_equal(heap_get_free_mem(test_heap),1000-sizeof(test_word));
char * test_word_2 = heap_get_proc_entity(test_heap,index);
assert_int_equal((int)test_word_2[5],(int)'!');
void * nullvoid = NULL;
heap_change_proc(test_heap,index,4,nullvoid);
test_word_2 = heap_get_proc_entity(test_heap,index);
assert_int_equal((int)test_word_2[5],(int)'!');
heap_free(test_heap);
}

static void heap_new_proc__int_index__heap_t_pt_int_mem_amount_and_void_pt_entity(void **state){
heap_t * test_heap = heap_new(10,100);
int test = 49;
void * test_void = &test;
int index;
int * int_for_assert;
for(int i = 0;i<10;i++){
    index = heap_new_proc(test_heap,sizeof(int),test_void);
    assert_int_equal(heap_get_free_mem(test_heap),100-sizeof(int)*(1+i));
    int_for_assert = (int *)heap_get_proc_entity(test_heap,index);
    assert_int_equal(49,*int_for_assert);
}
assert_int_equal(-1,heap_new_proc(test_heap,1,test_void));
heap_free_proc(test_heap,5);
heap_free_proc(test_heap,4);
heap_free_proc(test_heap,7);
assert_int_equal(4,heap_new_proc(test_heap,1,test_void));
assert_int_equal(5,heap_new_proc(test_heap,1,test_void));
assert_int_equal(7,heap_new_proc(test_heap,1,test_void));
heap_free_proc(test_heap,3);
printf("FREE MEM IS %i\n",heap_get_free_mem(test_heap));
assert_int_equal(-1,heap_new_proc(test_heap,500,test_void));
heap_free(test_heap);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(heap_new__heap_t_pt__int_max_proc_and_free_memory),
        cmocka_unit_test(heap_change_proc__int_error__heap_t_pt_int_mem_amount_and_void_pt_entity),
        cmocka_unit_test(heap_new_proc__int_index__heap_t_pt_int_mem_amount_and_void_pt_entity),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
