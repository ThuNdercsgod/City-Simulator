#include <cmath>
#include <iostream>
#include <stdexcept>

#include "old.hpp"

Old::Old(Location location, Location centerPoint, unsigned width, unsigned length)
    : Building(location)
{
    float distanceFromCenter = sqrt((centerPoint.x - location.x) * (centerPoint.x - location.x) -
                                    (centerPoint.y - location.y) * (centerPoint.y - location.y));

    unsigned min = (width < length) ? width : length;

    if (distanceFromCenter < (min / 8))
    {
        this->setLocationType(LocationType::Central);
    }
    else if (distanceFromCenter > (6 * min / 8))
    {
        this->setLocationType(LocationType::Outer);
    }
    else
    {
        this->setLocationType(LocationType::Normal);
    }
    this->setRent(this->getLocationType());
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
void Old::setRent(LocationType locationType)
{
    if (locationType == LocationType::Normal)
    {
        this->rent = 500;
    }
    else if (locationType == LocationType::Central)
    {
        this->rent = 500 * 2.5;
    }
    else if (locationType == LocationType::Outer)
    {
        this->rent = 500 - (0.2 * 500);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}