#include <iostream>
#include <stdexcept>

#include "building.hpp"
#include "modern.hpp"
#include "old.hpp"
#include "dormitory.hpp"

void Building::print() const
{
    this->printStatus();
    std::cout << "Residents: ...." << std::endl;

    // TODO print residents
}

double Building::getRent() const
{
    return this->rent;
}

Location Building::getLocation() const
{
    return this->location;
}

unsigned Building::getNumOfResidents() const
{
    return this->numOfResidents;
}

void Building::setRent(double rent)
{
    this->rent = rent;
}

void Building::setLocation(Location location)
{
    this->location = location;
}

Building *Factory(BuildingType type, Location location)
{
    switch (type)
    {
    case BuildingType::Modern:
        return new Modern(location);
    // case BuildingType::Old:
    //     return new Old(location);
    // case BuildingType::Dormitory:
    //     return new Dormitory(location);
    default:
        throw std::invalid_argument("Invalid building type");
    }
}