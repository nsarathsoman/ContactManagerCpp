#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data_access.h"
#include "sqlite3.h"

// int create_contact(contact *contact) 
// {    
//     char *sql = (char *) malloc(sizeof(char) * 2000);
//     strcat(sql, "INSERT INTO contact (name. number) VALUES(");
//     strcat(sql, contact->name); 
//     strcat(sql, ",");
//     itoa(contact->number, sql);
//     strcat(sql, ")");
//     char *zErrMsg = 0;
//     sqlite3 *db = get_connection(CONTACT_TABLE);
//     int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

//     if(rc != SQLITE_OK) 
//     {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }

//     close_connection(db);
//     return 0;
// }

contact* ContactDataAccess::get_contact(int id)
{    
    char *sql = (char *) malloc(sizeof(char) * 2000);
    strcat(sql, "SELECT id, name, number FROM contact WHERE id = ");
    itoa(id, sql);
    char *zErrMsg = 0;
    sqlite3 *db = get_connection(CONTACT_TABLE);
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    close_connection(db);
    contact *con = (contact*) malloc(sizeof(contact));
    contact *tmp = (contacts + (contact_count - 1));
    con->id = tmp->id;
    con->number = tmp->number;
    int name_len = 0;
    while(*(tmp->name + name_len) != '\0') name_len++;
    con->name = (char *)malloc(sizeof(char) * name_len);
    strcpy(con->name, tmp->name);
    free(contacts);
    return con;
}

// void update_contact(contact *contact)
// {
//     char *sql = (char *) malloc(sizeof(char) * 2000);
//     strcat(sql, "UPDATE contact SET name = ");
//     strcat(sql, contact->name);
//     strcat(sql, ", number = ");
//     itoa(contact->number, sql);
//     strcat(sql, " WHERE id = ");
//     itoa(contact->id, sql);
//     char *zErrMsg = 0;
//     sqlite3 *db = get_connection(CONTACT_TABLE);
//     int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

//     if(rc != SQLITE_OK) 
//     {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }

//     close_connection(db);
// }

// void delete_contact(int id)
// {
//     char *sql = (char *) malloc(sizeof(char) * 2000);
//     strcat(sql, "DELETE FROM contact WHERE id = ");
//     itoa(id, sql);
//     char *zErrMsg = 0;
//     sqlite3 *db = get_connection(CONTACT_TABLE);
//     int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

//     if(rc != SQLITE_OK) 
//     {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }

//     close_connection(db);
// }

sqlite3* ContactDataAccess::get_connection(char *db_name)
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

void ContactDataAccess::close_connection(sqlite3 *db)
{
    sqlite3_close(db);
}

int ContactDataAccess::callback(void *not_in_use, int argc, char **argv, char **az_col_name)
{
    contacts = (contact*)realloc(contacts, sizeof(contact) * ++contact_count);
    contact *con = (contacts + (contact_count - 1));

    con->id = atoi(argv[0]);
    con->name = argv[1];    
    con->number = atoi(argv[2]);
    printf("Out DB -- id %d, name %s, number %d\n", con->id, con->name, con->number);
    return 0;
}

int main() {
    ContactDataAccess data_access = new ContactDataAccess();
    contact *con = data_access.get_contact(1);
    printf("Out DB -- id %d, name %s, number %d\n", con->id, con->name, con->number);
    free(con);
    delete data_access;
    return 0;
}