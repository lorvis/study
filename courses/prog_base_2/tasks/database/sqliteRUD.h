#ifndef SQLITE_RUD_HEADER
#define SQLITE_RUD_HEADER

#include <stdlib.h>

sqlite3 * sqlite_init(const char * dbName,int * rc);

int sqlite_show_all(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc);

int sqlite_show_in_range(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc, int maxFailures, int minSuccesses);

int sqlite_delete_by_id(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc, int id);

int sqlite_insert(
    sqlite3 * db,
    sqlite3_stmt * stmt_to_form,
    int * rc,
    int id,
    int failures,
    int successes,
    const char * name,
    const char * birthdate,
    const char * country
);

#endif // SQLITE_RUD_HEADER
