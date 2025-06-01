#include <iostream>
#include <stdexcept>

#include "modern.hpp"

Modern::Modern(Location location)
{
    this->setLocation(location);
    this->setRent(location);
}

void Modern::printStatus() const
{
    std::cout << "Building type: " << this->getType()
              << "\nRent: " << this->rent
              << "\nResidents: " << this->getNumOfResidents()
              << std::endl;
}

const char *Modern::getType() const
{
    return "Modern";
}

double Modern::getRent() const
{
    return this->rent;
}

// Might throw std::invalid_argument
void Modern::setRent(Location location)
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