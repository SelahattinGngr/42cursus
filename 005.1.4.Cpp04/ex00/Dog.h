#ifndef DOG_H
#define DOG_H

#include "Animal.h"

class Dog : public Animal {
    public:
        Dog();
        Dog(const Dog& copy);
        Dog &operator=(const Dog& copy);
        ~Dog();
        void makeSound() const;
};

#endif
