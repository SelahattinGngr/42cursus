#include "Zombie.hpp"

zombie *newZombie(std::string name)
{
    zombie *z1 = new zombie();
    z1->setName(name);

    return z1;
}