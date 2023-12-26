#include "Cat.h"
#include "Dog.h"
#include "Brain.h"
#include "Animal.h"

int main()
{
    std::cout << "**********************" << std::endl; 
    const Animal* j = new Dog();
    std::cout << "---------------------" << std::endl; 
    const Animal* i = new Cat();
    std::cout << "**********************" << std::endl; 
    
    std::cout << j->getType() << std::endl;
    j->makeSound();
    std::cout << "---------------------" << std::endl;

    std::cout << i->getType() << std::endl;
    i->makeSound();
    std::cout << "---------------------" << std::endl;

    Cat cat;
    const Animal* test = &cat;
    test->makeSound();
    std::cout << "---------------------" << std::endl;
        
    Cat c;
    Dog f;
    std::cout <<"think of the Dog "<< f.getBrain()->ideas[99] << std::endl;
    std::cout <<"think of the cat " << c.getBrain()->ideas[99] << std::endl;
    
    std::cout << "**********************" << std::endl; 
    delete j;
    std::cout << "---------------------" << std::endl; 
    delete i;
    std::cout << "**********************" << std::endl; 

    return 0;
}