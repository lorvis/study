#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


typedef struct teammate teammate_t;
typedef struct scrum_master scrum_master_t;
typedef struct scrum_masters scrum_masters_t;
typedef struct sm_size sm_size_s;


scrum_masters_t * xml_sm_new(const char * xmlfilename);
void xm_sm_printOut(scrum_masters_t * to_print);
void xm_sm_free(scrum_masters_t * to_free);

