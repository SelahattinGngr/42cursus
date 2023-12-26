#ifndef Cat_H
#define Cat_H

#include "AAnimal.h"
#include "Brain.h"

class Cat : public AAnimal {
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
