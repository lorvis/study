#include "heap.h"
enum heap_errors {OBJECT_IS_NULL=100};

struct heap{
memory_t **process;
int free_mem;
int max_proc;
};

heap_t * heap_new(int max_proc_in, int free_mem_max){
heap_t * new_heap = malloc(sizeof(heap_t));
if(new_heap == NULL){
    puts("HEAP MALLOC ERROR!\n");
    return NULL;
    }
new_heap->process = malloc(sizeof(void*)*max_proc_in);
if(new_heap->process == NULL){
    puts("PROCESS MALLOC ERROR!\n");
    return NULL;
}
new_heap->free_mem = free_mem_max;
new_heap->max_proc = max_proc_in;
for(int i = 0; i<max_proc_in;i++){
new_heap->process[i] = NULL;
}
return new_heap;
}

void heap_free(heap_t * to_free){
for(int i = 0;i<to_free->max_proc;i++){
if(to_free->process[i]!=NULL)
memory_free(to_free->process[i]);
}
free(to_free->process);
free(to_free);
}

int heap_new_proc(heap_t * to_set, int mem_amount, void * entity_to_load){
    int i,non_null_proc = 0;
    if(to_set->free_mem - mem_amount < 0){
    printf("NOT ENOUGHT FREE SPACE!\n");
    return -1;
    }
for(i = 0;i < to_set->max_proc;i++){
if(to_set->process[i]==NULL){
    to_set->process[i] = memory_new(mem_amount,entity_to_load);
    break;
}
non_null_proc++;
}
if(non_null_proc==to_set->max_proc){
    puts("TOO MANY PROCESSES!\n");
    return -1;
}
to_set->free_mem -= mem_amount;
return i;
}

int heap_free_proc(heap_t * free_from, int index){
    if(free_from->process[index] == NULL)
        return 1;
free_from->free_mem += memory_get_alloc_num(free_from->process[index]);
memory_free(free_from->process[index]);
free_from->process[index] = NULL;
return 0;
}

void heap_change_proc(heap_t * change_in,int index, int proc_mem_alloc_num, void * entity){
if(entity == NULL){
    puts("TRYING TO INSERT NULL!\n");
    return;
}
change_in->free_mem+=memory_get_alloc_num(change_in->process[index]) - proc_mem_alloc_num;
memory_set_entity(change_in->process[index],proc_mem_alloc_num,entity);
return;
}

memory_t * heap_get_proc(heap_t * get_from, int index){
return get_from->process[index];
}

int heap_get_free_mem(heap_t * get_from){
return get_from->free_mem;
}

void * heap_get_proc_entity(heap_t * heap_of_proc,int proc_index){
return memory_get_entity(heap_get_proc(heap_of_proc,proc_index));
}
