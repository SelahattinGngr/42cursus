#ifndef CHARACTER_H
#define CHARACTER_H

#include "ICharacter.h"

class Character: public ICharacter {
    private:
        std::string name;
        AMateria    *inventory[4];
        Character();
    public:
        Character(std::string name);
        Character(const Character& copy);
        ~Character();
        Character &operator=(const Character& copy);
        std::string const & getName() const;
        void equip(AMateria* m);
        void unequip(int idx);
        void use(int idx, ICharacter& target);

};

#endif
