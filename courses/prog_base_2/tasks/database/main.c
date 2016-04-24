#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"
#include "sqliteRUD.h"

#define MAX_FAILURES 4
#define MIN_SUCCESSES 8

/* this is automatically called when result is ready */
//static int callback(void * uContext, int argc, char ** argv, char ** azColName);

int main(void)
{
    const char * dbFile = "ScrumMaster.db";

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);


    sqlite3_stmt * stmt = NULL;

    sqlite_show_all(db,stmt,&rc);

    puts("\n----------------------------------\n DELETE \n----------------------------------\n");

    sqlite_delete_by_id(db,stmt,&rc,2);

    sqlite_show_all(db,stmt,&rc);

    puts("\n----------------------------------\n INSERT \n----------------------------------\n");

    sqlite_insert(db,stmt,&rc,6,9,9,"Jeka","13-12-1933","Poland");

    sqlite_show_all(db,stmt,&rc);

     puts("\n----------------------------------\n SHOW IN RANGE \n----------------------------------\n");

    sqlite_show_in_range(db,stmt,&rc,MAX_FAILURES,MIN_SUCCESSES);


    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

//int main(void){
//    sqlite3 * db;
//    char * zErrMsg = 0;
//    int returnCode = 0;
//    const char * databaseFile = "PractDB.db";
//    const char * sqlScript = "SELECT * FROM Tank;";
//    void * userContext = NULL;
//
//    returnCode = sqlite3_open(databaseFile, &db);
//    if (SQLITE_OK != returnCode) {
//        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//        sqlite3_close(db);
//        return(1);
//    }
//
//    returnCode = sqlite3_exec(db, sqlScript, callback, userContext, &zErrMsg);
//    if (SQLITE_OK != returnCode) {
//        fprintf(stderr, "SQL error: %s\n", zErrMsg);
//        sqlite3_free(zErrMsg);
//    }
//    sqlite3_close(db);
//    return 0;
//}
//
//static int callback(void * uContext, int argc, char ** argv, char ** azColName) {
//    for (int i = 0; i < argc; i++) {
//        char * attr = azColName[i];
//        char * value = argv[i] ? argv[i] : "NULL";
//        printf("%s = %s\n", attr, value);
//    }
//    printf("\n");
//    return 0;
//}
