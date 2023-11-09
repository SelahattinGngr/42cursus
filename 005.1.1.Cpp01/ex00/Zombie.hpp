#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "iostream"

class zombie
{
private:
    std::string name;

public:
    zombie();
    zombie(std::string name);
    ~zombie();
    void setName(std::string name);
    std::string getName(void);
    void announce(void);
};

zombie *newZombie(std::string name);
void randomChump(std::string name);
#endif