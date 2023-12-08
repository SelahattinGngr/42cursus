#ifndef FIXED_HPP
#define FIXED_HPP

#include "iostream"

#define cout std::cout
#define endl std::endl

class Fixed {
	private:
		int  fixed_value;
		static const int fractional_value = 8;
	public:
		Fixed();
		Fixed(const Fixed &copyFixed);
		Fixed &operator=(Fixed const &fixed);
		~Fixed();
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif