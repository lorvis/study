#include "sqlite3.h"
#include "sqliteRUD.h"
sqlite3 * sqlite_init(const char * dbName,int * rc)
{
    sqlite3 * db = NULL;

    *rc = sqlite3_open(dbName,&db);

    if(SQLITE_OK != *rc)
    {
        printf("Can't Open\n");
        return 1;
    }

    return db;

}

int sqlite_show_all(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc)
{
    const char * sql = "SELECT * FROM ScrumMaster;";

    *rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt_to_form,NULL);

    if(SQLITE_OK != *rc)
    {
        printf("Can't prepare statement!\n");
        return 1;
    }

    while(1)
    {
        *rc = sqlite3_step(stmt_to_form);
        if(SQLITE_ERROR == *rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == *rc)
        {
            break;
        }
        else if (SQLITE_ROW == *rc)
        {
            int count = sqlite3_column_count(stmt_to_form);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt_to_form,i);
                puts("\n");
                const char * colType = sqlite3_column_decltype(stmt_to_form,i);
                const char * value =  sqlite3_column_text(stmt_to_form,i);
                printf("%10s [%7s] = %s",colName,colType, value);
            }
            puts("\n\n");
        }
    }
    return SQLITE_OK;
}


int sqlite_show_in_range(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc, int maxFailures, int minSuccesses)
{

    const char * sql = "SELECT * FROM ScrumMaster WHERE Successes > ? AND Failures < ?;";

    *rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt_to_form,NULL);

    sqlite3_bind_int(stmt_to_form,1,minSuccesses);
    sqlite3_bind_int(stmt_to_form,2,maxFailures);

    if(SQLITE_OK != *rc)
    {
        printf("Can't prepare statement!\n");
        return 1;
    }

    while(1)
    {
        *rc = sqlite3_step(stmt_to_form);
        if(SQLITE_ERROR == *rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == *rc)
        {
            break;
        }
        else if (SQLITE_ROW == *rc)
        {
            int count = sqlite3_column_count(stmt_to_form);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt_to_form,i);
                puts("\n");
                const char * colType = sqlite3_column_decltype(stmt_to_form,i);
                const char * value =  sqlite3_column_text(stmt_to_form,i);
                printf("%10s [%7s] = %s",colName,colType, value);
            }
            puts("\n\n");
        }
    }
    return SQLITE_OK;
}

int sqlite_delete_by_id(sqlite3 * db, sqlite3_stmt * stmt_to_form, int * rc, int id)
{

    if(id<0)
    {
        puts("Negative ID!");
        return 1;
    }

    const char * sql = "DELETE FROM ScrumMaster WHERE ID = ?;";

    *rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt_to_form,NULL);

    sqlite3_bind_int(stmt_to_form,1,id);

    if(SQLITE_OK != *rc)
    {
        printf("Can't prepare statement!\n");
        return 1;
    }

    while(1)
    {
        *rc = sqlite3_step(stmt_to_form);
        if(SQLITE_ERROR == *rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == *rc)
        {
            break;
        }
        else if (SQLITE_ROW == *rc)
        {
            int count = sqlite3_column_count(stmt_to_form);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt_to_form,i);
                puts("\n");
                const char * colType = sqlite3_column_decltype(stmt_to_form,i);
                const char * value =  sqlite3_column_text(stmt_to_form,i);
                printf("%10s [%7s] = %s",colName,colType, value);
            }
            puts("\n\n");
        }
    }
    return SQLITE_OK;
}

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
)
{

    const char * sql = "INSERT INTO ScrumMaster VALUES (?,?,?,?,?,?) ;";

    *rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt_to_form,NULL);

    sqlite3_bind_int(stmt_to_form,1,id);
    sqlite3_bind_int(stmt_to_form,2,failures);
    sqlite3_bind_int(stmt_to_form,3,successes);
    sqlite3_bind_text(stmt_to_form,4,name,strlen(name),SQLITE_STATIC);
    sqlite3_bind_text(stmt_to_form,5,birthdate,strlen(birthdate),SQLITE_STATIC);
    sqlite3_bind_text(stmt_to_form,6,country,strlen(country),SQLITE_STATIC);

    if(SQLITE_OK != *rc)
    {
        printf("Can't prepare statement!\n");
        return 1;
    }


        *rc = sqlite3_step(stmt_to_form);

        if(SQLITE_ERROR == *rc)
        {
            printf("Step error\n");
            return 1;
        }

    return SQLITE_OK;
}
