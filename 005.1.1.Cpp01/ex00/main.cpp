#include "Zombie.hpp"

int main()
{
    zombie z1;
    z1.setName("foo");
    z1.announce();

    zombie z2("boo");
    z2.announce();

    zombie *z3;
    z3 = newZombie("boo");
    z3->announce();

    randomChump("foo");

    delete (z3);
}