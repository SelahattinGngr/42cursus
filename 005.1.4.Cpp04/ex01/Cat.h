#ifndef Cat_H
#define Cat_H

#include "Animal.h"
#include "Brain.h"

class Cat : public Animal {
    private:
        Brain *brain;
    public:
        Cat();
        Cat(const Cat& copy);
        Cat &operator=(const Cat& copy);
        ~Cat();
        void makeSound() const;
        Brain *getBrain() const;
};

#endif
