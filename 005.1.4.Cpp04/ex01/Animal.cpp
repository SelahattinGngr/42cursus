#include "Animal.h"

Animal::Animal() {
    type = "Animal";
    std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(std::string type): type(type) { std::cout << "Animal constructor called" << std::endl; }

Animal::Animal(const Animal& copy) {
    *this = copy;
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal& copy) {
    this->type = copy.type;
    return (*this);
}

Animal::~Animal() { std::cout << "Animal destructor called" << std::endl; }

std::string Animal::getType() const { return (type); }

void Animal::setType(std::string type) { this->type = type; }

void Animal::makeSound() const { std::cout << "regular animal sound" << std::endl; }