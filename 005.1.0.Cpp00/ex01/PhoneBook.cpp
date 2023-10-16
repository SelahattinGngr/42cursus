#include "phoneBook.hpp"

int mystrlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

int isnum(char s, int i)
{
    if (48 <= s && s <= 48 + i)
        return (1);
    return (0);
}

void writeScreen(char *str)
{
    int len;
    int i;

    len = mystrlen(str);
    i = -1;
    if (len >= 10)
    {
        while (++i < 9)
            std::cout << str[i];
        std::cout << ".";
    }
    else
    {
        while (++i < (10 - len))
            std::cout << " ";
        std::cout << str;
    }
    std::cout << "|";
}

void phoneBook::setIndex(const int _index)
{  
    this->index = _index;
}

void phoneBook::add()
{
    char fn[50];
    char ln[50];
    char nn[50];
    char pn[50];
    char ds[50];
    int i;
    std::cout << "firstname: ";
    std::cin >> fn;
    std::cout << "lastname: ";
    std::cin >> ln;
    std::cout << "nickname: ";
    std::cin >> nn;
    std::cout << "darkest Secret: ";
    std::cin >> ds;
    std::cout << "phone number: ";
    std::cin >> pn;
    i = index % 8;
    if (fn != nullptr && ln != nullptr && nn != nullptr && pn != nullptr && ds != nullptr)
    {
        c1[i].fillContact(fn, ln, nn, ds, pn);
        index++;
    }
}

void phoneBook::search()
{
    int max;
    char iter;
    int i;
    std::cout << std::endl;
    std::cout << std::right << "Index    "
              << "|";
    std::cout << std::right << "First Name"
              << "|";
    std::cout << std::right << "Last Name "
              << "|";
    std::cout << std::right << "Nick Name "
              << "|";
    std::cout << std::endl;
    if (index >= 8)
        max = 8;
    else
        max = index;
    for (i = 0; i < max; i++)
    {
        std::cout << i << "        |";
        writeScreen(c1[i].getFirstname());
        writeScreen(c1[i].getLastname());
        writeScreen(c1[i].getNickname());
        std::cout << std::endl;
    }
    while (1)
    {
        std::cout << "index: " << std::endl;
        std::cin >> iter;
        if (isnum(iter, max))
            i = (int)iter - 48;
        else
        {
            std::cout << "Please enter a valid number >:(" << std::endl;
            continue;
        }
        if ((i >= max) || (i< 0))
        {
            std::cout << "wrong index" << std::endl;
        }
        else
        {
            std::cout << "first name: " << c1[i].getFirstname() << std::endl;
            std::cout << "last name: " << c1[i].getLastname() << std::endl;
            std::cout << "nick name: " << c1[i].getNickname() << std::endl;
            std::cout << "darkest secret: " << c1[i].getDarkestsecret() << std::endl;
            std::cout << "phone number: " << c1[i].getPhonenumber() << std::endl;
            break;
        }
    }
}