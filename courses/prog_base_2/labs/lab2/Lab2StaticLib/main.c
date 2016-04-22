#include <stdio.h>

struct queue {
int size;
int tail;
int * body;
};

typedef struct queue queue_t;

queue_t * queue_new(int size){
queue_t * new_queue = malloc(sizeof(queue_t));
new_queue->body = malloc(sizeof(int)*size);
new_queue->size = size;
new_queue->tail = 0;
return new_queue;
}

void queue_free(queue_t * to_free){
free(to_free->body);
free(to_free);
return;
}

int queue_size(queue_t * to_examine){
return to_examine->tail;
}

int queue_max_size(queue_t * to_examine){
return to_examine->size;
}


void queue_add(queue_t * add_into,int value){
if(add_into->tail>=add_into->size){
    puts("QUEUE IS FULL\n");
    return;
}
add_into->body[add_into->tail] = value;
add_into->tail++;
}

void queue_show(queue_t * to_show){
    puts("QUEUE:");
for(int i = 0; i < to_show->tail; i++)
    printf("%i ",to_show->body[i]);
}

int queue_remove(queue_t * remove_from){
int res = remove_from->body[0];
for(int i = 1;i<remove_from->tail;i++)
    remove_from->body[i-1] = remove_from->body[i];
remove_from->tail--;
return res;
}


int queue_get(queue_t * get_from,int index){
return get_from->body[index];
}
