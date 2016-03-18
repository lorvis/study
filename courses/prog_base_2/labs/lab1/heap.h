#ifndef HEADER_HEAP_INCLUDED
#define HEADER_HEAP_INCLUDED
#include "memory.h"
typedef struct heap heap_t;

heap_t * heap_new(int max_proc_in, int free_mem_max);
void heap_free(heap_t * to_free);
int heap_new_proc(heap_t * to_set, int mem_amount, void * entity_to_load);
int heap_free_proc(heap_t *, int index);
memory_t * heap_get_proc(heap_t * get_from, int index);
void heap_change_proc (heap_t * change_in,int index, int proc_mem_alloc_num, void * entity);
int heap_get_free_mem(heap_t * get_from);
void * heap_get_proc_entity(heap_t * heap_of_proc,int proc_index);
#endif // HEADER_INCLUDED
