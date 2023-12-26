#include "Cat.h"

Cat::Cat() {
    std::cout << "Cat constructor called" << std::endl;
    AAnimal::type = "Cat";
    this->brain = new Brain();
}

Cat::Cat(const Cat& copy) {
    std::cout << "Cat copy constructor called" << std::endl;
    *this = copy;
}

Cat &Cat::operator=(const Cat& copy) {
    AAnimal::type = copy.type;
    this->brain = copy.brain;
    return (*this);
}

void Cat::makeSound() const {
    std::cout << "meow meow" << std::endl;
}

Brain *Cat::getBrain() const {
    return brain;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
    delete brain;
}
