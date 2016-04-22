#ifndef QUEUE_HEADER_INCLUDED
#define QUEUE_HEADER_INCLUDED

typedef struct queue queue_t;

queue_t * queue_new(int size);

void queue_free(queue_t * to_free);

int queue_size(queue_t * to_examine);

int queue_max_size(queue_t * to_examine);

int queue_remove(queue_t * remove_from);

void queue_show(queue_t * to_show);

void queue_add(queue_t * add_into,int value);

int queue_get(queue_t * get_from,int index);

#endif // QUEUE_HEADER_INCLUDED
