#include "Ice.h"
#include "ICharacter.h"

Ice::Ice(): AMateria("ice") {
    std::cout << "Ice constructor called\n";
}

Ice::Ice(const Ice& copy) {
    *this = copy;
}

Ice &Ice::operator=(const Ice& copy) {
    this->type = copy.getType();
    return *this;
}

std::string const &Ice::getType() const {
    return (this->type);
}

Ice::~Ice() {
    std::cout << "Ice destructor called\n";
}

Ice *Ice::clone() const {
    Ice *ret = new Ice;
    return ret;
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}
