#include "data_access.h"
#include "sqlite3.h"

#define CONTACT_TABLE "contact"

int create_contact(contact *contact) 
{
    char *sql = "INSERT INTO contact (name. number) VALUES(" + contact->name + "," + contact->number + ")";
    char *zErrMsg = 0;
    sqlite3 *db = get_connection(CONTACT_TABLE);
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    close_connection(db);
}

contact* get_contact(int id)
{
    char *sql = "INSERT INTO contact (name. number) VALUES(" + contact->name + "," + contact->number + ")";
    char *zErrMsg = 0;
    sqlite3 *db = get_connection(CONTACT_TABLE);
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    close_connection(db);
}

void update_contact(contact *contact);

void delete_contact(int id);

sqlite3* get_connection(char *db_name)
{
    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    
    if(rc) 
    {
        fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    return db;
}

void close_connection(sqlite3 *db)
{
    sqlite3_close(db);
}

int callback(void *not_in_use, int argc, char **argv, char **az_col_name)
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}