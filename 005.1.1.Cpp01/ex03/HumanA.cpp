#include "HumanA.hpp"
// C++ dilinde referanslar başlatıcı liste kullanılmadan doğrudan başlatılamaz.
HumanA::HumanA(std::string name_, Weapon &weapon_) : name(name_), weapon(weapon_)
{
}
HumanA::~HumanA() {}

void HumanA::attack()
{
    std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}