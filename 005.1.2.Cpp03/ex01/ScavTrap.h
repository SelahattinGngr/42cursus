#ifndef SCAVTRAP_H
#define SCAVTRAP_H

#include "ClapTrap.h"

class ScavTrap: public ClapTrap {
    public:
        ScavTrap();
        ScavTrap(std::string _name);
        ScavTrap(const ScavTrap& copy);
        ScavTrap &operator=(const ClapTrap& copy);
        ~ScavTrap();
        void attack(const std::string& target);
        void guardGate();
};

#endif