#ifndef BRAIN_H
#define BRAIN_H

#include <iostream>

class Brain {
    public:
        std::string ideas[100];
        Brain();
        Brain(const Brain& b);
        Brain &operator=(const Brain& b);
        virtual ~Brain();
};

#endif
