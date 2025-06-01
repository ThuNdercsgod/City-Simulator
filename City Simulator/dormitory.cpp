#include <iostream>
#include <stdexcept>

#include "dormitory.hpp"

Dormitory::Dormitory(Location location)
{
    this->setLocation(location);
    this->setRent(location);
}

void Dormitory::printStatus() const
{
    std::cout << "Building type: " << this->getType()
              << "\nRent: " << this->rent
              << "\nResidents: " << this->getNumOfResidents()
              << std::endl;
}

const char *Dormitory::getType() const
{
    return "Dormitory";
}

double Dormitory::getRent() const
{
    return this->rent;
}

// Might throw std::invalid_argument
void Dormitory::setRent(Location location)
{
    if (location == Location::Normal)
    {
        this->rent = 40;
    }
    else if (location == Location::Central)
    {
        this->rent = 40 * 2.5;
    }
    else if (location == Location::Outer)
    {
        this->rent = 40 - (0.2 * 40);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}