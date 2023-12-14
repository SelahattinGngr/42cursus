#include "Fixed.hpp"

Fixed::Fixed(int fixedValue) : fixed_value(fixedValue){
	std::cout << "default constructor" << std::endl;
}

Fixed::Fixed(const Fixed &copyFixed){
	std::cout << "copy constructor" << std::endl;
	*this = copyFixed;
}

Fixed::~Fixed() {
	std::cout << "destructor" << std::endl;
}

Fixed &Fixed::operator=(Fixed const& fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &fixed)
		this->fixed_value = fixed.getRawBits();
	return (*this);
}

int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->fixed_value);
}

void Fixed::setRawBits(int const raw) {
	this->fixed_value = raw;	
}
