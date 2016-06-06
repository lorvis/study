#include <windows.h>

#include "tower.h"
#include "http.h"
#include "cJSON.h"

int towers_get_id_by_index(const char * dbName,int index) {
towers_t * towlist = towers_new();
towers_fillFromSql("tower.db",towlist);
return towlist->towarr[index].id;
}

int towers_get_row_count_Filtrated(char * dbName, int levels, double height) {
 const char * dbFile = dbName;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    char * sql = malloc(100);

    sprintf(sql,"SELECT * FROM Towers WHERE Levels < ? AND \"Height(m)\" > ?");

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    sqlite3_bind_int(stmt,1,levels);
    sqlite3_bind_double(stmt,2,height);

    free(sql);

    if(SQLITE_OK != rc)
    {
        return -1;
    }
    int rowcount = 0;
    while(1)
    {
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            rowcount++;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rowcount;
}

char * towers_get_JSON_string(const char * dbName, int isFiltrated, int levels, double height) {
towers_t * towlist = towers_new();

if(isFiltrated)
towers_fillFromSql_Filtrated(dbName,towlist,levels,height);
else
towers_fillFromSql("tower.db",towlist);

cJSON * JSONArr = cJSON_CreateArray();
for(int i = 0; i<towlist->amount;i++){
cJSON * new_JSON = cJSON_CreateObject();
cJSON_AddItemToObject(new_JSON,"ID",cJSON_CreateNumber(towlist->towarr[i].id));
cJSON_AddItemToObject(new_JSON,"Height(m)",cJSON_CreateNumber(towlist->towarr[i].height));
cJSON_AddItemToObject(new_JSON,"Name",cJSON_CreateString(towlist->towarr[i].name));
cJSON_AddItemToObject(new_JSON,"Material",cJSON_CreateString(towlist->towarr[i].material));
cJSON_AddItemToObject(new_JSON,"Levels",cJSON_CreateNumber(towlist->towarr[i].levels));
cJSON_AddItemToObject(new_JSON,"Building date",cJSON_CreateString(towlist->towarr[i].buildingDate));
cJSON_AddItemToArray(JSONArr,new_JSON);
}
char * jString = cJSON_Print(JSONArr);
cJSON_Delete(JSONArr);
return jString;
}

char * towers_get_JSON_elem (const char * dbName, int elemIndex) {
towers_t * towlist = towers_new();
towers_fillFromSql("tower.db",towlist);
cJSON * new_JSON = cJSON_CreateObject();
cJSON_AddItemToObject(new_JSON,"ID",cJSON_CreateNumber(towlist->towarr[elemIndex].id));
cJSON_AddItemToObject(new_JSON,"Height(m)",cJSON_CreateNumber(towlist->towarr[elemIndex].height));
cJSON_AddItemToObject(new_JSON,"Name",cJSON_CreateString(towlist->towarr[elemIndex].name));
cJSON_AddItemToObject(new_JSON,"Material",cJSON_CreateString(towlist->towarr[elemIndex].material));
cJSON_AddItemToObject(new_JSON,"Levels",cJSON_CreateNumber(towlist->towarr[elemIndex].levels));
cJSON_AddItemToObject(new_JSON,"Building date",cJSON_CreateString(towlist->towarr[elemIndex].buildingDate));
char * jString = cJSON_Print(new_JSON);
cJSON_Delete(new_JSON);
return jString;
}

int tower_exists_by_ID(char * dbName,int elemID){
int response = 0;
towers_t * towlist = towers_new();
towers_fillFromSql("tower.db",towlist);
for(int i = 0; i < sqlite3_get_row_count(dbName,"Towers"); i++){
    if(towlist->towarr[i].id == elemID)
    {
        response = 1;
        break;
    }
}
towers_free(towlist);
return response;
}

char * towers_get_string_elem(const char * dbName, int elemIndex) {
towers_t * towlist = towers_new();
towers_fillFromSql("tower.db",towlist);
char result[4000];
sprintf(result," ID: %i <br> Height(m): %lf <br> Name: %s <br> Material:%s <br> Levels: %i <br> Building date: %s <br> <a href=\"http://127.0.0.1:27015/towers/\"> Back to list </a> <br>",\
        towlist->towarr[elemIndex].id,\
        towlist->towarr[elemIndex].height,\
        towlist->towarr[elemIndex].name,\
        towlist->towarr[elemIndex].material,\
        towlist->towarr[elemIndex].levels,\
        towlist->towarr[elemIndex].buildingDate);
return result;
}

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


int towers_show_all_sql(char * dbName)
{

    const char * dbFile = dbName;

    int rc = 0;


    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    const char * sql = "SELECT * FROM Towers;";

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement!\n");
        return 1;
    }

    while(1)
    {
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            int count = sqlite3_column_count(stmt);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt,i);
                puts("\n");
                const char * colType = sqlite3_column_decltype(stmt,i);
                const char * value =  sqlite3_column_text(stmt,i);
                printf("%10s [%7s] = %s",colName,colType, value);
            }
            puts("\n\n");
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return SQLITE_OK;
}


int sqlite3_get_row_count(char * dbName, char * tablename){

    const char * dbFile = dbName;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    char * sql = malloc(100);

    sprintf(sql,"SELECT * FROM %s;",tablename);

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    free(sql);

    if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement during simple counting!\n");
        return 1;
    }
    int rowcount = 0;
    while(1)
    {
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            rowcount++;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rowcount;
}


int towers_fillFromSql(char * dbName,towers_t * towlist)
{
    towlist->amount = sqlite3_get_row_count(dbName,"Towers");


    const char * dbFile = dbName;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    towlist->towarr = malloc(sizeof(tower_t)*towlist->amount);

    for(int i = 0; i < towlist->amount;i++)
    {
        towlist->towarr[i].name = malloc(100);
        towlist->towarr[i].material = malloc(100);
        towlist->towarr[i].buildingDate = malloc(100);
    }

    const char * sql = "SELECT * FROM Towers;";

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement during simple filling!\n");
        return 1;
    }

int j = 0;
    while(1)
    {
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            int count = sqlite3_column_count(stmt);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt,i);

                if(strcmp(colName,"ID")==0)
                    towlist->towarr[j].id = sqlite3_column_int(stmt,i);
                if(strcmp(colName,"Height(m)")==0)
                    towlist->towarr[j].height = sqlite3_column_double(stmt,i);
                if(strcmp(colName,"Name")==0)
                    strcpy(towlist->towarr[j].name,sqlite3_column_text(stmt,i));
                if(strcmp(colName,"Material")==0)
                    strcpy(towlist->towarr[j].material,sqlite3_column_text(stmt,i));
                if(strcmp(colName,"Levels")==0)
                    towlist->towarr[j].levels = sqlite3_column_int(stmt,i);
                if(strcmp(colName,"BuildingDate")==0)
                    strcpy(towlist->towarr[j].buildingDate,sqlite3_column_text(stmt,i));

            }
            j++;
            puts("\n\n");
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return SQLITE_OK;
}

int towers_fillFromSql_Filtrated(char * dbName,towers_t * towlist,int levels,double height)
{
    towlist->amount = towers_get_row_count_Filtrated(dbName,levels,height);

    if(towlist->amount<0)
    {
        puts("counting towers error!");
        return 1;
    }
    const char * dbFile = dbName;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    towlist->towarr = malloc(sizeof(tower_t)*towlist->amount);

    for(int i = 0; i < towlist->amount;i++)
    {
        towlist->towarr[i].name = malloc(100);
        towlist->towarr[i].material = malloc(100);
        towlist->towarr[i].buildingDate = malloc(100);
    }

    const char * sql = "SELECT * FROM Towers WHERE Levels < ? AND \"Height(m)\" > ?;";

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement during filling!\n");
        return 1;
    }
//
    sqlite3_bind_int(stmt,1,levels);
    sqlite3_bind_double(stmt,2,height);

int j = 0;
    while(1)
    {
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            int count = sqlite3_column_count(stmt);
            for(int i = 0; i < count; i++)
            {
                const char * colName = sqlite3_column_name(stmt,i);

                if(strcmp(colName,"ID")==0)
                    towlist->towarr[j].id = sqlite3_column_int(stmt,i);
                if(strcmp(colName,"Height(m)")==0)
                    towlist->towarr[j].height = sqlite3_column_double(stmt,i);
                if(strcmp(colName,"Name")==0)
                    strcpy(towlist->towarr[j].name,sqlite3_column_text(stmt,i));
                if(strcmp(colName,"Material")==0)
                    strcpy(towlist->towarr[j].material,sqlite3_column_text(stmt,i));
                if(strcmp(colName,"Levels")==0)
                    towlist->towarr[j].levels = sqlite3_column_int(stmt,i);
                if(strcmp(colName,"BuildingDate")==0)
                    strcpy(towlist->towarr[j].buildingDate,sqlite3_column_text(stmt,i));

            }
            j++;
            puts("\n\n");
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return SQLITE_OK;
}

int tower_insert(char * dbName, http_request_t * request)
{

    const char * dbFile = dbName;

    int vlom = 0;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    char * sql = "INSERT INTO Towers VALUES (NULL,?,?,?,?,?);";

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);


        if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement during insertion!\n");
        return 1;
    }
    sqlite3_bind_double(stmt,1,atof(request->form[0].value));
    sqlite3_bind_text(stmt,2,request->form[1].value,strlen(request->form[1].value),SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,request->form[2].value,strlen(request->form[2].value),SQLITE_STATIC);
    sqlite3_bind_int(stmt,4,atoi(request->form[3].value));
    sqlite3_bind_text(stmt,5,request->form[4].value,strlen(request->form[4].value),SQLITE_STATIC);

    rc = sqlite3_step(stmt);

            if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }

    return SQLITE_OK;
}

int tower_delete(char * dbName, int index)
{

    const char * dbFile = dbName;

    int rc = 0;

    sqlite3 * db = sqlite_init(dbFile,&rc);

    sqlite3_stmt * stmt = NULL;

    char * sql = "DELETE FROM Towers WHERE ID = ?";

    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);

    sqlite3_bind_int(stmt,1,towers_get_id_by_index("towers.db",index));


        if(SQLITE_OK != rc)
    {
        printf("Can't prepare statement during deleting!\n");
        return 1;
    }

    rc = sqlite3_step(stmt);

            if(SQLITE_ERROR == rc)
        {
            printf("Step error\n");
            return 1;
        }

    return SQLITE_OK;
}

void towers_print_out(towers_t * towlist){
for(int i = 0; i < towlist->amount;i++) {
    printf("ID = %i, Height(m) = %lf, Name = %s, Material = %s, Levels = %i, Building Date : %s",towlist->towarr[i].id,towlist->towarr[i].height,towlist->towarr[i].name,towlist->towarr[i].material,towlist->towarr[i].levels,towlist->towarr[i].buildingDate);
    puts("\n");
}
}

towers_t * towers_new(){
towers_t * newtowlist = malloc(sizeof(towers_t));
return newtowlist;
}

void towers_free(towers_t * towlist){
for(int i = 0; i < towlist->amount; i++)
{
    free(towlist->towarr[i].name);
    free(towlist->towarr[i].material);
    free(towlist->towarr[i].buildingDate);
}
free(towlist->towarr);
free(towlist);
}


