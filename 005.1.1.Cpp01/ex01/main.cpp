#include "Zombie.hpp"

int main()
{
    zombie *z1 = zombieHorde(5, "haydariye");
    zombie *z2 = zombieHorde(3, "haydar");
    int i;

    for (i = 0; i < 5; i++)
        z1[i].announce();
    for (i = 0; i < 3; i++)
        z2[i].announce();
    delete[] (z1);
    delete[] (z2);
}