#ifndef MATERIASOURCE_H
#define MATERIASOURCE_H

#include "IMateriaSource.h"

class MateriaSource: public IMateriaSource {
    private:
        AMateria    *inventory[4];
    public:
        MateriaSource();
        MateriaSource(const MateriaSource& copy);
        MateriaSource &operator=(const MateriaSource& copy);
        ~MateriaSource();
        void learnMateria(AMateria*);
        AMateria* createMateria(std::string const & type);
};

#endif
