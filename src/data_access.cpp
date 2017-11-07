#include<stdio.h>
#include<stdlib.h>
#include "data_access.h"
#include "sqlite3.h"

#define CONTACT_TABLE "contact"

contact *contacts;
int contact_count = 0;

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
    char *sql = "SELECT id, name, number FROM contact WHERE id = " + id;
    char *zErrMsg = 0;
    sqlite3 *db = get_connection(CONTACT_TABLE);
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    close_connection(db);
    contact *contact = (*contact) malloc(sizeof(contact));
    memcpy(contact, *(contacts + (contact_count - 1)), sizeof(contact));
    free(contacts);
    return contact;
}

void update_contact(contact *contact)
{
    char *sql = "UPDATE contact SET name = " + contact->name + ", number = " + contact->number + " WHERE id = " + contact->id;
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

void delete_contact(int id)
{
    char *sql = "DELETE FROM contact WHERE id = " + contact->id;
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
    contacts = (contact*)realloc(contacts, sizeof(contact) * ++contact_count);
    contact *contact = *(contacts + (contact_count - 1));

    contact->id = atoi(argv[0]);
    contact->name = argv[1];    
    contact->number = atoi(argv[2]);
    return 0;
}