#ifndef DOG_H
#define DOG_H

#include "Animal.h"
#include "Brain.h"

class Dog : public Animal {
    private:
        Brain *brain;
    public:
        Dog();
        Dog(const Dog& copy);
        Dog &operator=(const Dog& copy);
        ~Dog();
        void makeSound() const;
        Brain *getBrain() const;
};

#endif
