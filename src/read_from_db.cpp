#include<stdio.h>
#include "sqlite3.h"

static int callback(void *not_in_use, int argc, char **argv, char **az_col_name);

int main(int argc, char **argv) 
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s DATABASE SQL-STMT\n", argv[0]);
        return(1);
    }

    rc = sqlite3_open(argv[1], &db);

    if(rc) 
    {
        fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }

    rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
}

static int callback(void *not_in_use, int argc, char **argv, char **az_col_name)
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}