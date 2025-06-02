#include <cmath>
#include <iostream>
#include <stdexcept>

#include "dormitory.hpp"

Dormitory::Dormitory(Location location, Location centerPoint, unsigned width, unsigned length)
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
void Dormitory::setRent(LocationType locationType)
{
    if (locationType == LocationType::Normal)
    {
        this->rent = 40;
    }
    else if (locationType == LocationType::Central)
    {
        this->rent = 40 * 2.5;
    }
    else if (locationType == LocationType::Outer)
    {
        this->rent = 40 - (0.2 * 40);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}