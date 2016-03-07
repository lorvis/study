#ifndef THERE_IS_HEADER
#define THERE_IS_HEADER
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct set_t set_t;

void set_add_range (set_t * set_reciever,int low_edge, int high_edge); // OK
void set_delete_range (set_t * set_losing,int low_edge, int high_edge); //OK
set_t * set_absolute_complement (set_t * set_A, set_t * set_B, char * if_delete_param);// OK
set_t * set_relative_complement (set_t * set_A, set_t * set_B, char * if_delete_param); //A/B  OK
set_t * _set_intersection (set_t * set_A, set_t * set_B, char * if_delete_param);
set_t * set_merge (set_t * set_A, set_t * set_B, char * if_delete_param); // OK
int set_measure_power (set_t * set_A); // OK
set_t * set_new (int size); //OK
void set_delete(set_t * to_delete);
void set_print_out(set_t * to_print);
int set_print_size(set_t * set_with_size); //also returns it OK
int set_get_element(set_t * set_A,int position); //added in unit-test
#endif // THERE_IS_HEADER
