#ifndef WRONGCAT_H
#define WRONGCAT_H

#include "WrongAnimal.h"

class WrongCat : public WrongAnimal {
    public:
        WrongCat();
        WrongCat(const WrongCat& copy);
        WrongCat &operator=(const WrongCat& copy);
        ~WrongCat();
        void makeSound() const;
};

#endif
