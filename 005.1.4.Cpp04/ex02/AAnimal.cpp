#include "AAnimal.h"

AAnimal::AAnimal() {
    type = "Animal";
    std::cout << "Animal constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type): type(type) { std::cout << "Animal constructor called" << std::endl; }

AAnimal::AAnimal(const AAnimal& copy) {
    *this = copy;
    std::cout << "Animal copy constructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal& copy) {
    this->type = copy.type;
    return (*this);
}

AAnimal::~AAnimal() { std::cout << "Animal destructor called" << std::endl; }

std::string AAnimal::getType() const { return (type); }

void AAnimal::setType(std::string type) { this->type = type; }

void AAnimal::makeSound() const { std::cout << "regular animal sound" << std::endl; }