#include "memory.h"

struct memory{
 void * entity;
 int allocated_memory;
};

memory_t * memory_new(int mem_amount, void * entity_to_load){
memory_t * new_mem = malloc(sizeof(memory_t));
if(new_mem == NULL)
    printf("MALLOC ERROR!\n");
new_mem->entity = malloc(mem_amount);
for(int i = 0;i<mem_amount;i++){
((char *)new_mem->entity)[i] = 0;
(((char *)new_mem->entity)[i]) = ((char *)entity_to_load)[i];
}
if(new_mem->entity == NULL)
    printf("MALLOC ERROR!\n");
new_mem->allocated_memory = mem_amount;
return new_mem;
}

int memory_free(memory_t * to_free){
free(to_free->entity);
free(to_free);
}

void * memory_get_entity(memory_t * to_get){
return to_get->entity;
}

void memory_set_entity(memory_t * to_set, int mem_amount, void * entity_to_load){
to_set->allocated_memory = mem_amount;
for(int i = 0;i<mem_amount;i++){
((char *)to_set->entity)[i] = 0;
(((char *)to_set->entity)[i]) = ((char *)entity_to_load)[i];
}
}

int memory_get_alloc_num(memory_t * to_get){
return to_get->allocated_memory;
}
