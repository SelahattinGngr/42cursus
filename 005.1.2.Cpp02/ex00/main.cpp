#include "Fixed.hpp"

int main(void) {
    Fixed a;
    Fixed b( a );
    Fixed c;

    c = b;

    cout << &a << endl;
    cout << &b << endl;
    cout << &c << endl;

    cout << a.getRawBits() << endl;
    cout << b.getRawBits() << endl;
    cout << c.getRawBits() << endl;
    
    return 0;
}