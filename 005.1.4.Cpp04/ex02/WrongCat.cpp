#include "WrongCat.h"

WrongCat::WrongCat() {
    std::cout << "WrongCat constructor called" << std::endl;
    WrongAnimal::type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& copy) {
    std::cout << "WrongCat copy constructor called" << std::endl;
    *this = copy;
}

WrongCat &WrongCat::operator=(const WrongCat& copy) {
    WrongAnimal::type = copy.type;
    return (*this);
}

void WrongCat::makeSound() const { std::cout << "meow meow" << std::endl; }

WrongCat::~WrongCat() { std::cout << "WrongCat destructor called" << std::endl; }
