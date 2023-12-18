#include "FragTrap.h"

int main() {
	FragTrap e("Steve Griffin");
	FragTrap f("Brain dogson");
	
	e.highFivesGuys();
	e.attack("Louis Griffin");
	e.takeDamage(101);
	e.takeDamage(1);
	e.attack("Louis Griffin");
	f.highFivesGuys();
	return (0);
}