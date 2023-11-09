#include "iostream"

int main()
{
    std::string str = "HI THIS IS BRAIN";
    std::string *stringPTR = &str;
    std::string &stringREF = str;

    std::cout << "memmory address of str: " << &str << std::endl;
    std::cout << "memmory address held by pointer: " << stringPTR << std::endl;
    std::cout << "memmory addres held by reference: " << &stringREF << std::endl;
    std::cout << "value of str: " << str << std::endl;
    std::cout << "value of pointed by pointer: " << *stringPTR << std::endl;
    std::cout << "value of pointed by reference: " << stringREF << std::endl;
}