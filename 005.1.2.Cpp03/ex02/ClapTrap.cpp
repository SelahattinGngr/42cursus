#include "ClapTrap.h"

ClapTrap::ClapTrap() {
    this->name = "default man";
    this->hitPoints = 10;
    this->energyPoints = 10;
    this->attackDamage = 0;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap constructor called\n";   
}

ClapTrap::ClapTrap(const ClapTrap& copy) { *this = copy; }

ClapTrap::~ClapTrap() { std::cout << "ClapTrap destructor Called\n"; }

ClapTrap &ClapTrap::operator=(const ClapTrap& copy) {
    this->name = copy.getName();
    this->hitPoints = copy.getHitPoints();
    this->energyPoints = copy.getEnergyPoints();
    this->attackDamage = copy.getAttackDamage();
    return (*this);
}

std::string ClapTrap::getName() const { return (this->name); }

int ClapTrap::getHitPoints() const { return (this->hitPoints); }

int ClapTrap::getEnergyPoints() const { return (this->energyPoints); }

int ClapTrap::getAttackDamage() const { return (this->attackDamage); }

void ClapTrap::setName(std::string name) { this->name = name; }

void ClapTrap::setHitPoints(int amount) { this->hitPoints = amount; }

void ClapTrap::setEnergyPoints(int amount) { this->energyPoints = amount; }

void ClapTrap::setAttackDamage(int amount) { this->attackDamage = amount; }

void ClapTrap::attack(const std::string& target) {
    if (this->hitPoints <= 0)
        return ;
    if (this->energyPoints <= 0) {
        std::cout <<  this->getName() << " does not have any energy points to attack\n";
        return ;
    }
    std::cout << this->getName() << " attacks " << target << ", causing " << this->getAttackDamage() << " points of damage!\n";
    this->energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->hitPoints <= 0)
        return ;
    if (this->hitPoints <= (int)amount) {
        std::cout << this->getName() << " is died\n";
        this->hitPoints -= amount;
        return ;
    }
    std::cout << this->getName() << " has take " << amount << " point of damage\n";
    this->hitPoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->hitPoints <= 0)
        return ;
    if (this->energyPoints <= 0) {
        std::cout <<  this->getName() << "does not have any energy points to repair itself\n";
        return ;
    }
    std::cout << this->getName() << " has repaired " << amount << " point of itself\n";
    this->energyPoints--;
    this->hitPoints += amount;
}