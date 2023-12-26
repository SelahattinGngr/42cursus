#include "AMateria.h"
#include "ICharacter.h"

AMateria::AMateria() {
    std::cout << "AMateria constructor called\n";
}

AMateria::AMateria(std::string const & type): type(type) {
        std::cout << "AMateria constructor called\n";
}

AMateria::AMateria(const AMateria& copy): type(copy.getType()) {
    
}

// We don't use copy assigment operator
AMateria &AMateria::operator=(const AMateria& copy) {
    (void)copy;
    return *this;
}

AMateria::~AMateria() {
    std::cout << "AMateria destructor called\n";
}

std::string const & AMateria::getType() const {
    return (this->type);
}

void AMateria::use(ICharacter& target) {
	std::cout << "AMateria used on " << target.getName() << std::endl;
}
