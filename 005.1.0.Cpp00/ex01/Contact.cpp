#include "contact.hpp"

static void myStrcpy(char *s1, const char *s2)
{
    int i;
    i = -1;
    while (s2[++i])
        s1[i] = s2[i];
    s1[i] = '\0';
}

void contact::fillContact(const char *fn, const char *ln, const char *nn, const char *ds, const char *pn)
{
    myStrcpy(firstName, fn);
    myStrcpy(lastName, ln);
    myStrcpy(nickname, nn);
    myStrcpy(darkestSecret, ds);
    myStrcpy(phoneNumber, pn);
}

char *contact::getFirstname()
{
    return firstName;
}

char *contact::getLastname()
{
    return lastName;
}

char *contact::getNickname()
{
    return nickname;
}

char *contact::getDarkestsecret()
{
    return darkestSecret;
}

char *contact::getPhonenumber()
{
    return phoneNumber;
}