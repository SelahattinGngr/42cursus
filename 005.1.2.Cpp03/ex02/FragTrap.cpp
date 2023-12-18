#include "FragTrap.h"

FragTrap::FragTrap(): ClapTrap() {
    this->setName("default man");
    this->setHitPoints(100);
    this->setEnergyPoints(50);
    this->setAttackDamage(20);
    std::cout << "FragTrap default destructor called\n";
}

FragTrap::FragTrap(std::string name): ClapTrap(name) {
    this->setHitPoints(100);
    this->setEnergyPoints(100);
    this->setAttackDamage(30);
    std::cout << "FragTrap constructor called\n";
}

FragTrap::FragTrap(const FragTrap& copy) { *this = copy; }

FragTrap::~FragTrap() { std::cout << "FragTrap destructor called\n"; }

FragTrap &FragTrap::operator=(const ClapTrap& copy) {
    this->setName(copy.getName());
    this->setEnergyPoints(copy.getEnergyPoints());
    this->setHitPoints(copy.getHitPoints());
    this->setAttackDamage(copy.getAttackDamage());
    return (*this);
}

void    FragTrap::highFivesGuys() { std::cout << "FragTrap " << this->getName() << " want's to high five\n"; }