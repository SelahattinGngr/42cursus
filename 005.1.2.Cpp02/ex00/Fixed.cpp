#include "Fixed.hpp"

Fixed::Fixed(){
	cout << "default constructor" << endl;
	this->fixed_value = 0;
}

Fixed::Fixed(int a){
	cout << "default constructor" << endl;
	this->fixed_value = a;
}

Fixed::Fixed(const Fixed &copyFixed){
	cout << "copy constructor" << endl;
	*this = copyFixed;
}

Fixed::~Fixed() {
	cout << "destructor" << endl;
}

Fixed &Fixed::operator=(Fixed const& fixed) {
	cout << "Copy assignment operator called" << endl;
	if (this != &fixed)
		this->fixed_value = fixed.getRawBits();
	return (*this);
}

int Fixed::getRawBits() const {
	cout << "getRawBits member function called" << endl;
	return (this->fixed_value);
}

void Fixed::setRawBits(int const raw) {
	this->fixed_value = raw;	
}
