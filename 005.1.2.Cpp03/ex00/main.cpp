#include "ClapTrap.h"

int main()
{
	ClapTrap a("Dipper Pines");
	ClapTrap b("Mabel Pines");
	ClapTrap c(b);
	a.takeDamage(5);
	a.attack("Bill Cipher");
	a.takeDamage(5);
	a.takeDamage(5);
	a.beRepaired(5);
	std::cout << "\n\n\n";
	
	b.beRepaired(3);
	for (int i = 0; i < 12; i++)
		b.attack("Gideon Gleeful");
	b.takeDamage(13);
	b.beRepaired(10);
	std::cout << "\n\n\n";

	c.setHitPoints(100);
	c.setEnergyPoints(5);
	c.setAttackDamage(10);
	for (int i = 0; i < 10; i++)
		c.attack("Stan Pines");
	c.takeDamage(90);
	c.beRepaired(5);
	c.takeDamage(20);
	return 0;
}