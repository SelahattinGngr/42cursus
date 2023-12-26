#include "Cat.h"

Cat::Cat() {
    std::cout << "Cat constructor called" << std::endl;
    Animal::type = "Cat";
}

Cat::Cat(const Cat& copy) {
    std::cout << "Cat copy constructor called" << std::endl;
    *this = copy;
}

Cat &Cat::operator=(const Cat& copy) {
    Animal::type = copy.type;
    return (*this);
}

void Cat::makeSound() const { std::cout << "meow meow" << std::endl; }

Cat::~Cat() { std::cout << "Cat destructor called" << std::endl; }
