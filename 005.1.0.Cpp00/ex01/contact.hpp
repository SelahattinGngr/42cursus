#ifndef CONTACT_H
#define CONTACT_H

#include "iostream"

class contact
{
private:
    char firstName[50];
    char lastName[50];
    char nickname[50];
    char darkestSecret[50];
    char phoneNumber[50];

public:
    void fillContact(const char *fn, const char *ln, const char *nn, const char *ds, const char *pn);
    char *getFirstname();
    char *getLastname();
    char *getNickname();
    char *getDarkestsecret();
    char *getPhonenumber();
};

#endif