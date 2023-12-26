#ifndef CURE_H
#define CURE_H

#include "AMateria.h"

class Cure: public AMateria {
    public:
        Cure();
        Cure(const Cure& copy);
        Cure &operator=(const Cure& copy);
        std::string const & getType() const;
        Cure *clone() const;
        void use(ICharacter& target);
        ~Cure();
};

#endif
