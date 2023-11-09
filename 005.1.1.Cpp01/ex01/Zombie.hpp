#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "iostream"

class zombie
{
private:
    std::string name;

public:
    zombie();
    ~zombie();
    void setName(std::string name);
    void announce(void);
    std::string getName(void);
};

zombie *zombieHorde(int N, std::string name);
#endif