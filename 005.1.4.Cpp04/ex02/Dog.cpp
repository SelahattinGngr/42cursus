#include "Dog.h"

Dog::Dog() {
    std::cout << "Dog constructor called" << std::endl;
    AAnimal::type = "Dog";
    this->brain = new Brain();
}

Dog::Dog(const Dog& copy) {
    std::cout << "Dog copy constructor called" << std::endl;
    *this = copy;
}

Dog &Dog::operator=(const Dog& copy) {
    AAnimal::type = copy.type;
    this->brain = copy.brain;
    return (*this);
}

void Dog::makeSound() const { std::cout << "woof woof" << std::endl; }

Brain *Dog::getBrain() const { return this->brain; }

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete brain;
}
