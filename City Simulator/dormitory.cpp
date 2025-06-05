#include <cmath>
#include <stdexcept>

#include "dormitory.hpp"

// Might throw std::invalid_argument
Dormitory::Dormitory(Location location, Location centerPoint, unsigned length, unsigned width)
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

    switch (this->getLocationType())
    {
    case LocationType::Normal:
        this->setRent(40);
        break;
    case LocationType::Central:
        this->setRent(40 * 2.5);
        break;
    case LocationType::Outer:
        this->setRent(40 - (0.2 * 40));
        break;
    default:
        throw std::invalid_argument("Invalid location for Building!");
        break;
    }
}

const char *Dormitory::getType() const
{
    return "Dormitory";
}