#include "HumanB.hpp"

HumanB::HumanB(std::string name_) : name(name_), weapon(NULL) {}

HumanB::~HumanB() {}

void HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
}

void HumanB::attack()
{
    if (this->weapon == NULL || this->weapon->getType().empty())
        std::cout << this->name << " has no weapon :(" << std::endl;
    else
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
}