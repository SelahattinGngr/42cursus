#include "Zombie.hpp"

zombie::zombie()
{
}

zombie::~zombie()
{
    std::cout << "Zombie " << this->name << " has been destroyed" << std::endl;
}

void zombie::setName(std::string name)
{
    this->name = name;
}

std::string zombie::getName(void)
{
    return this->name;
}

void zombie::announce(void)
{
    std::cout << getName() << ": BraiiiiiiinnnzzzZ..." << std::endl;
}