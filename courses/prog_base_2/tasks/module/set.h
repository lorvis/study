#ifndef THERE_IS_HEADER
#define THERE_IS_HEADER
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct set_t set_t;

void set_add_range (set_t * set_reciever,int low_edge, int high_edge);
void set_delete_range (set_t * set_losing,int low_edge, int high_edge);
set_t * set_absolute_complement (set_t * set_A, set_t * set_B, char * if_delete_param);
set_t * set_relative_complement (set_t * set_A, set_t * set_B, char * if_delete_param); //A/B
set_t * _set_intersection (set_t * set_A, set_t * set_B, char * if_delete_param);
set_t * set_merge (set_t * set_A, set_t * set_B, char * if_delete_param);
int set_measure_power (set_t * set_A);
set_t * set_new (int size);
void set_delete(set_t * to_delete);
void set_print_out(set_t * to_print);
void set_print_size(set_t * set_with_size);
#endif // THERE_IS_HEADER
