#include "Zombie.hpp"

zombie *zombieHorde(int N, std::string name)
{
    zombie *zmb = new zombie[N];
    for (int i = 0; i < N; i++)
        zmb[i].setName(name);
    return zmb;
}