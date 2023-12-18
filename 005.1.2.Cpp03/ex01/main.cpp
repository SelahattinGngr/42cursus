#include "ScavTrap.h"

int main()
{
	ClapTrap a("spongebob");
	a.attack("patrick starson");
	std::cout << "--------------------" << std::endl;
	ScavTrap d("Captain Jack Sparrow");
	ScavTrap e("Captain Hector Barbossa");
	d.attack("Davy Jones");
	d.beRepaired(22);
	d.takeDamage(21);
	d.beRepaired(22);
	d.guardGate();
	ScavTrap f(d);
	d.takeDamage(200);
	d.attack("Davy Jones");
	f.attack("Davy Jones");
	f.attack("Davy Jones");
	f.attack("Davy Jones");
	f.attack("Davy Jones");
	f.takeDamage(1000);
	std::cout << "---------------------" << std::endl;
	e.attack("Captain Armando Salazar");
	e.takeDamage(20);
	e.attack("Captain Armando Salazar");
	e.takeDamage(101);
	e.takeDamage(15);
	e.attack("Captain Armando Salazar");
	std::cout << "---------------------" << std::endl;
	return 0;
}