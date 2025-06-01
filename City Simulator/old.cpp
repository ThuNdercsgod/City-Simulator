#include <iostream>
#include <stdexcept>

#include "old.hpp"

Old::Old(Location location)
{
    this->setLocation(location);
    this->setRent(location);
}

void Old::printStatus() const
{
    std::cout << "Building type: " << this->getType()
              << "\nRent: " << this->rent
              << "\nResidents: " << this->getNumOfResidents()
              << std::endl;
}

const char *Old::getType() const
{
    return "Old";
}

double Old::getRent() const
{
    return this->rent;
}

// Might throw std::invalid_argument
void Old::setRent(Location location)
{
    if (location == Location::Normal)
    {
        this->rent = 500;
    }
    else if (location == Location::Central)
    {
        this->rent = 500 * 2.5;
    }
    else if (location == Location::Outer)
    {
        this->rent = 500 - (0.2 * 500);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}