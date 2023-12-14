#ifndef FIXED_HPP
#define FIXED_HPP

#include "iostream"

class Fixed {
	private:
		int  fixed_value;
		static const int fractional_value = 8;
	public:
		Fixed(int fixedValue = 0);
		Fixed(const Fixed &copyFixed);
		Fixed &operator=(Fixed const &fixed);
		~Fixed();
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif