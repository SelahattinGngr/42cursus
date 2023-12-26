#include "Dog.h"
#include "Cat.h"
#include "WrongCat.h"

int main()
{
    {
        const Animal *meta = new Animal();
        const Animal *j = new Dog();
        const Animal *i = new Cat();
        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        i->makeSound();
        j->makeSound();
        meta->makeSound();

        delete meta;
        delete j;
        delete i;
    }

    {
        const WrongAnimal* meta = new WrongAnimal();
        const WrongAnimal* cat = new WrongCat();

        std::cout << meta->getType() << " " << std::endl;
        std::cout << cat->getType() << " " << std::endl;
        cat->makeSound();
        meta->makeSound();
        delete meta;
        delete cat;            
    }

    return 0;
}