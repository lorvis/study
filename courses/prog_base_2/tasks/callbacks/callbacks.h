#ifndef CALLBACKS_HEADER_INCLUDED
#define CALLBACKS_HEADER_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef void (*oneCharIn_CB)(char symbolToPlayWith);
typedef void (*charAndStringIn_CB)(char stringToPlayWith[11],char symbolToPlayWith);

struct list_for_CB{
oneCharIn_CB single_arg_CB;
charAndStringIn_CB double_arg_CB;
};

typedef struct list_for_CB CB_list;

void detect(CB_list list_for_detect);
#endif // CALLBACKS_HEADER_INCLUDED
