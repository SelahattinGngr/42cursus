#include "Zombie.hpp"

void randomChump(std::string name)
{
    zombie z1;
    z1.setName(name);
    z1.announce();
}