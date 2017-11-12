#pragma once

class Contact 
{
public:
    int id;
    char *name;    
    int number;
};

class IContactDataAccess 
{
public:
    virtual Contact* getContact(int id) = 0;
    virtual void createContact(Contact *contact) = 0;
    virtual void updateContact(Contact *contact) = 0;
    virtual void deleteContact(int id) = 0;
};