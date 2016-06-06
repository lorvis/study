#ifndef TOWER_HEADER_INCLUDE
#define TOWER_HEADER_INCLUDE
#include <stdlib.h>
#include "sqlite3.h"

typedef struct tower tower_t;
typedef struct towers towers_t;

struct tower {
int id;
double height;
char * name;
char * material;
int levels;
char * buildingDate;
};

struct towers {
int amount;
tower_t * towarr;
};

sqlite3 * sqlite_init(const char * dbName,int * rc);

int towers_fillFromSql (char * dbName, towers_t * towlist);

char * towers_get_JSON_string(const char * dbName, int isFiltrated, int levels, double height);

char * towers_get_JSON_elem (const char * dbName, int elemIndex);

char * towers_get_string_elem(const char * dbName, int elemIndex);

int tower_exists_by_ID(char * dbName,int index);

int tower_delete(char * dbName, int index);

int towers_get_id_by_index(const char * dbName,int index);

int towers_show_all_sql(char * dbName);

towers_t * towers_new();

void towers_free(towers_t * towlist);

int sqlite3_get_row_count(char * dbName, char * tablename);

void towers_print_out(towers_t * towlist);

#endif // TOWER_HEADER_INCLUDE
