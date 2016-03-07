#include "Set.h"

struct set_t {
int size;
int * arr;
};

set_t * set_new (int arr_size) {
set_t * aNew_set = (set_t *)malloc(sizeof(set_t));
aNew_set->arr = (int *)malloc(sizeof(int)*arr_size);
aNew_set->size = arr_size;
for(int i=0;i<aNew_set->size;i++){
aNew_set->arr[i] = 0;
}
if(aNew_set==NULL){
printf("MALLOC ERROR!!!");
exit(1);
} else {
return aNew_set;
}
}

void set_delete (set_t * to_delete) {
free(to_delete->arr);
free(to_delete);
return;
}

void set_add_range (set_t * set_reciever, int low_edge, int high_edge) {
for(int i = low_edge;(i<set_reciever->size)&&(i<high_edge+1);i++){
set_reciever->arr[i] = 1;
}
return;
}


void set_print_out(set_t * to_print){
puts("\n Elements in set:");
for(int i = 0; i<to_print->size;i++){
    if(to_print->arr[i]){
        printf(" %i",i);
    }
}
return;
}

void set_delete_range (set_t * set_losing,int low_edge, int high_edge) {
for(int i = low_edge;(i<set_losing->size)&&(i<high_edge+1);i++){
set_losing->arr[i] = 0;
}
}

set_t * set_merge (set_t * set_A, set_t * set_B, char * if_delete_param){
    // if_delete_param - "del 1" to delete set_A and "del 2" to set_B after operation,
    // also there is "del both"
size_t minsize;
if(set_A->size<=set_B->size) {
    minsize = set_A->size;
} else {
minsize = set_B->size;
}
set_t * merged = (set_t *)malloc(sizeof(set_t));
if(merged==NULL){
puts("MALLOC PUT NULL!");
}
merged->arr = (int *)malloc(sizeof(int)*minsize);
if(merged->arr==NULL){
puts("MALLOC PUT NULL!");
}
merged->size = minsize;
for(int i = 0;i<minsize;i++){
merged->arr[i]=set_A->arr[i]|set_B->arr[i];
}
if (strcmp(if_delete_param,"del 1")==0) {
    set_delete(set_A);
}
if (strcmp(if_delete_param,"del 2")==0) {
    set_delete(set_B);
}
if (strcmp(if_delete_param,"del both")==0) {
    set_delete(set_A);
    set_delete(set_B);
    }
    return merged;
}

set_t * _set_intersection (set_t * set_A, set_t * set_B, char * if_delete_param){
    // if_delete_param - "del 1" to delete set_A and "del 2" to set_B after operation,
    // also there is "del both"
size_t minsize;
if(set_A->size<=set_B->size) {
    minsize = set_A->size;
} else {
minsize = set_B->size;
}
set_t * intersected = (set_t *)malloc(sizeof(set_t));
if(intersected==NULL){
puts("MALLOC PUT NULL!");
}
intersected->arr = (int *)malloc(sizeof(int)*minsize);
if(intersected->arr==NULL){
puts("MALLOC PUT NULL!");
}
intersected->size = minsize;
for(int i = 0;i<minsize;i++){
intersected->arr[i]=set_A->arr[i]&set_B->arr[i];
}
if (strcmp(if_delete_param,"del 1")==0) {
    set_delete(set_A);
}
if (strcmp(if_delete_param,"del 2")==0) {
    set_delete(set_B);
}
if (strcmp(if_delete_param,"del both")==0) {
    set_delete(set_A);
    set_delete(set_B);
    }
    return intersected;
}

int set_print_size(set_t * set_with_size){
printf(" size of set = %i\n",set_with_size->size);
return set_with_size->size;
}

set_t * set_absolute_complement (set_t * set_A, set_t * set_B, char * if_delete_param){
    // if_delete_param - "del 1" to delete set_A and "del 2" to set_B after operation,
    // also there is "del both"
size_t minsize;
if(set_A->size<=set_B->size) {
    minsize = set_A->size;
} else {
minsize = set_B->size;
}
set_t * complemented = (set_t *)malloc(sizeof(set_t));
if(complemented==NULL){
puts("MALLOC PUT NULL!");
}
complemented->arr = (int *)malloc(sizeof(int)*minsize);
if(complemented->arr==NULL){
puts("MALLOC PUT NULL!");
}
complemented->size = minsize;
for(int i = 0;i<minsize;i++){
complemented->arr[i]=set_A->arr[i]^set_B->arr[i];
}
if(if_delete_param==NULL){return complemented;}
if (strcmp(if_delete_param,"del 1")==0) {
    set_delete(set_A);
}
if (strcmp(if_delete_param,"del 2")==0) {
    set_delete(set_B);
}
if (strcmp(if_delete_param,"del both")==0) {
    set_delete(set_A);
    set_delete(set_B);
    }
    return complemented;
}

int set_measure_power (set_t * set_A){
int count = 0;
for(int i = 0;i<set_A->size;i++){
count+=(set_A->arr[i]!=0);
}
return count;
}

set_t * set_relative_complement (set_t * set_A, set_t * set_B, char * if_delete_param) {
    //A/B!!
    // if_delete_param - "del 1" to delete set_A and "del 2" to set_B after operation,
    // also there is "del both"
size_t minsize;
if(set_A->size<=set_B->size) {
    minsize = set_A->size;
} else {
minsize = set_B->size;
}
set_t * complemented = (set_t *)malloc(sizeof(set_t));
if(complemented==NULL){
puts("MALLOC PUT NULL!");
}
complemented->arr = (int *)malloc(sizeof(int)*minsize);
if(complemented->arr==NULL){
puts("MALLOC PUT NULL!");
}
complemented->size = minsize;
for(int i = 0;i<minsize;i++){
complemented->arr[i]=(set_A->arr[i])&(~(set_B->arr[i]));
}
if (strcmp(if_delete_param,"del 1")==0) {
    set_delete(set_A);
}
if (strcmp(if_delete_param,"del 2")==0) {
    set_delete(set_B);
}
if (strcmp(if_delete_param,"del both")==0) {
    set_delete(set_A);
    set_delete(set_B);
    }
    return complemented;
}

int set_get_element(set_t * set_A,int position){ //Added in unit-tests
return set_A->arr[position];
}
