typedef struct contact {
    int id;
    char *name;
    int number;
} contact;

int create_contact(contact *contact);

contact* get_contact(int id);

void update_contact(contact *contact);

void delete_contact(int id);