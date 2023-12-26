#ifndef ICE_H
#define ICE_H

#include "AMateria.h"

class Ice: public AMateria {
    public:
        Ice();
        Ice(const Ice& copy);
        Ice &operator=(const Ice& copy);
        std::string const & getType() const;
        Ice *clone() const;
        void use(ICharacter& target);
        ~Ice();
};

#endif
