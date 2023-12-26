#ifndef DOG_H
#define DOG_H

#include "AAnimal.h"
#include "Brain.h"

class Dog : public AAnimal {
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
