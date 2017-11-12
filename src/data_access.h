#include<string.h> 

typedef struct contact {
    int id;
    char *name;
    int number;
} contact;

class ContactDataAccess {
    public:
    // int create_contact(contact *contact);
    contact* get_contact(int id);
    sqlite3* get_connection(char *db_name);
    void close_connection(sqlite3 *db);
    int callback(void *not_in_use, int argc, char **argv, char **az_col_name);

    private:
    char *CONTACT_TABLE = "contact";
    contact *contacts;
    int contact_count = 0;

// void update_contact(contact *contact);

// void delete_contact(int id);
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}  

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}  