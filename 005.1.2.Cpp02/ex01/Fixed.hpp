#include "iostream"

class Fixed
{
private:
    int fixed;
    static const int fract_val = 8;
public:
    Fixed();
    Fixed(const int fi);
    Fixed(const float ff);
    Fixed(const Fixed& copy);
    ~Fixed();

    int	getRawBits() const;
    void    setRawBits(int const raw);
    Fixed &operator=(const Fixed& newFixed);
    float toFloat( void ) const;
    int toInt( void ) const;
};
std::ostream &operator<<(std::ostream &o, const Fixed& fixed);