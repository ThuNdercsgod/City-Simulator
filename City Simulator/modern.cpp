#include <stdexcept>

#include "modern.hpp"

Modern::Modern(Location location)
{
    this->setLocation(location);
    this->setRent(location);
}

const char *Modern::getType() const
{
    return "Modern";
}

double Modern::getRent() const
{
    return this->rent;
}

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