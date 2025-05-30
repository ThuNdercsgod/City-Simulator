#include <iostream>
#include <stdexcept>

#include "dormitory.hpp"

Dormitory::Dormitory(Location location)
{
    this->setLocation(location);
    this->setRent(location);
}

Building *Dormitory::clone() const
{
    return new Dormitory(*this);
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

void Dormitory::setRent(Location location)
{
    if (location == Location::Normal)
    {
        this->rent = 1000;
    }
    else if (location == Location::Central)
    {
        this->rent = 1000 * 2.5;
    }
    else if (location == Location::Outer)
    {
        this->rent = 1000 - (0.2 * 1000);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}