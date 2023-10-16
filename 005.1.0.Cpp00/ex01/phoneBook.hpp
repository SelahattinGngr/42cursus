#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "contact.hpp"

class phoneBook
{
private:
    int index;
    contact c1[9];

public:
    void add();
    void search();
    void setIndex(int x);
};

#endif