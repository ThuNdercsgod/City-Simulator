#include <cmath>
#include <iostream>
#include <stdexcept>

#include "modern.hpp"

Modern::Modern(Location location, Location centerPoint, unsigned width, unsigned length)
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
void Modern::setRent(LocationType locationType)
{
    if (locationType == LocationType::Normal)
    {
        this->rent = 1000;
    }
    else if (locationType == LocationType::Central)
    {
        this->rent = 1000 * 2.5;
    }
    else if (locationType == LocationType::Outer)
    {
        this->rent = 1000 - (0.2 * 1000);
    }
    else
    {
        throw std::invalid_argument("Invalid location for Building!");
    }
}