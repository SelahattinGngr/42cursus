#include "Dog.h"

Dog::Dog() {
    std::cout << "Dog constructor called" << std::endl;
    Animal::type = "Dog";
}

Dog::Dog(const Dog& copy) {
    std::cout << "Dog copy constructor called" << std::endl;
    *this = copy;
}

Dog &Dog::operator=(const Dog& copy) {
    Animal::type = copy.type;
    return (*this);
}

void Dog::makeSound() const { std::cout << "woof woof" << std::endl; }

Dog::~Dog() { std::cout << "Dog destructor called" << std::endl; }
