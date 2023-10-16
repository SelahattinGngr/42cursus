#include "contact.hpp"
#include "phoneBook.hpp"

int mystrcmp(char *s1, const char *s2)
{
    int i;

    i = -1;
    while (s1[++i] || s2[i])
        if (s1[i] != s2[i])
            return 0;

    return 1;
}

int main()
{
    phoneBook p1;
    char input[10];

    p1.setIndex(0);
    while (1)
    {
        std::cout << "> ";
        std::cin >> input;
        if (mystrcmp(input, "EXIT"))
            break;
        else if (mystrcmp(input, "ADD"))
            p1.add();
        else if (mystrcmp(input, "SEARCH"))
            p1.search();
        else
            std::cout << "wrong input" << std::endl;
    }
}
