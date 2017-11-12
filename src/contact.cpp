#include<cstdlib>
#include<iostream>
#include<cstring>

#include "contact.h"

using namespace std;

class ContactDataAccess : public IContactDataAccess
{
private:
    Contact *contacts;
    int contactCount;

public:

    ContactDataAccess() 
    {
        cout<<"Object created"<<endl;
    }

    ~ContactDataAccess() 
    {
        cout<<"Object Deleted"<<endl;
    }

    Contact* getContact(int id) 
    {
        for(int i = 0; i < contactCount; i++) 
        {
            Contact *con = contacts + i;
            if(con->id == id)
            {
                return con;
            }
        }

        return 0;
    }

    void createContact(Contact *contact)
    {        
        contacts = (Contact*)realloc(contacts, sizeof(Contact) * (contactCount + 1));
        Contact *con = contacts + contactCount++;
        con->id = contact->id;
        if(contact->name) 
        {
            con->name = (char *)malloc(sizeof(contact->name));
            strcpy(con->name, contact->name);
        }        
        con->number = contact->number;        
    }

    void updateContact(Contact *contact)
    {
        Contact *con = NULL;
        for(int i = 0; i < contactCount; i++) 
        {            
            if(contact->id == (contacts + i)->id)
            {
                con = (contacts + i);
                con->id = contact->id;
                if(sizeof(con->name) < sizeof(contact->name)) {
                    con->name = (char *)malloc(sizeof(contact->name));
                }
                strcpy(con->name, contact->name);
                con->number = contact->number;
                break;
            }
        }

        if(NULL == con) {
            throw "Contact not found for id " + contact->id;
        }
        
    }

    void deleteContact(int id)
    {

    }
};

int main() 
{
    ContactDataAccess *cda = new ContactDataAccess();

    Contact *contact = new Contact();
    contact->id = 1;
    char name[] = "Sarath";    
    contact->name = (char *)malloc(sizeof(name));
    strcpy(contact->name, name);    
    contact->number = 12312;

    cda->createContact(contact);

    delete contact;

    Contact *con = cda->getContact(1);    
    cout<<"id: "<<con->id<<", Name: "<<con->name<<", num: "<<con->number<<endl;

    char tempname[] = "sadasfffffffsaaaaaaaaaa";
    con->name = (char *)malloc(sizeof(tempname));
    strcpy(con->name, tempname);
    cda->updateContact(con);

    // *con = cda->getContact(1);
    cout<<"id: "<<con->id<<", Name: "<<con->name<<", num: "<<con->number<<endl;

    delete con;
    delete cda;
    return 0;
}