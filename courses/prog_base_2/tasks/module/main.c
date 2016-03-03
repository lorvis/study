
#include "Set.h"
int main()
{
    printf("Hello world!\n");
    set_t * set_A = set_new(10);
    set_t * set_B = set_new(7);
    set_t * set_C;
    set_add_range(set_A,0,11);
    set_add_range(set_B,3,5);
    puts("\n\n Set_A after add");
    set_print_out(set_A);
    set_delete_range(set_A,3,11);
    puts("\n\n Set_A after delete");
    set_print_out(set_A);
    puts("\n\n Set_B after add");
    set_print_out(set_B);
    set_C = set_merge(set_A,set_B,"none");
    puts("\n\n Set_C - result of merge");
    set_print_out(set_C);
    set_delete_range(set_A,0,10);
    set_add_range(set_A,4,7);
    puts("\n\n another set_A");
    set_print_out(set_A);
    set_delete(set_C);
    set_A = _set_intersection(set_A,set_B,"del 1");
    puts("\n\n set_A after intersection with set_B");
    set_print_out(set_A);
    puts("\n\n set_A size after intersection \n");
    set_print_size(set_A);
    set_delete_range(set_A,4,5);
    set_add_range(set_A,1,1);
        set_add_range(set_A,3,4);
    puts("\n\n another set_A");
    set_print_out(set_A);
     puts("\n\n set_B");
    set_print_out(set_B);
    set_C = set_absolute_complement(set_A,set_B,"none");
    puts("\n\n set_C - absolute_complement of set_A and set_B");
    set_print_out(set_C);

    printf("\n Power of set_C = %i",set_measure_power(set_C));
    set_delete(set_C);
    set_add_range(set_A,0,10);
    puts("\n\n set_A");
    set_print_out(set_A);
    set_delete_range(set_B,3,5);
    set_add_range(set_B,2,4);
    puts("\n\n set_B");
    set_print_out(set_B);
    set_C = set_relative_complement(set_A,set_B,"none");
    puts("\n\n set_C - relative_complement of set_A and set_B");
    set_print_out(set_C);
    set_delete(set_A);
    set_delete(set_B);
    set_delete(set_C);
    return 0;
}
