#include "bulding.hpp"

Location Building::getLocation() const
{
    return this->location;
}

unsigned Building::getNumOfResidents() const
{
    return this->numOfResidents;
}

void Building::setLocation(Location location)
{
    this->location = location;
}