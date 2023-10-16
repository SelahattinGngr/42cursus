#include "iostream"

int ft_toupper(char x)
{
    if (97 <= x && 122 >= x)
        x -= 32;
    return (x);
}

int main(int ac, char **av)
{
    if (ac == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
        int i;
        int j;

        i = 1;

        while (av[i])
        {
            j = 0;
            while (av[i][j])
            {
                av[i][j] = ft_toupper(av[i][j]);
                j++;
            }
            std::cout << av[i];
            printf("%s", av[i]);
            i++;
        }
    }
}