/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 01:21:20 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/08/01 13:22:25 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure(): AMateria("cure") {
    std::cout << "Cure constructor called\n";
}

Cure::Cure(const Cure& copy) {
    *this = copy;
}

Cure &Cure::operator=(const Cure& copy) {
    this->type = copy.getType();
    return *this;
}

std::string const & Cure::getType() const {
    return (this->type);
}

Cure::~Cure() {
    std::cout << "Cure destructor called\n";
}

Cure *Cure::clone() const {
    Cure *ret = new Cure;
    return ret;
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " <<  target.getName() << "\'s wounds *\n";
}
