#ifndef HEADER_MEMORY_INCLUDED
#define HEADER_MEMORY_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct memory memory_t;
memory_t * memory_new(int mem_amount, void * entity_to_load);
int memory_free(memory_t * to_free);
void * memory_get_entity(memory_t * to_get);
void memory_set_entity(memory_t * to_set, int mem_amount, void * entity_to_load);
int memory_get_alloc_num(memory_t * to_get);
#endif // HEADER_MEMORY_INCLUDED
