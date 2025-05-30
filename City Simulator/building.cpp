#include <iostream>
#include <stdexcept>

#include "building.hpp"
#include "dormitory.hpp"
#include "modern.hpp"
#include "old.hpp"

#include "resident.hpp"

void Building::addResident(Resident *resident)
{
    if (this->numOfResidents == 0)
    {
        this->residents = new Resident *[1];
        this->residents[0] = resident;
        this->numOfResidents = 1;
    }
    else
    {
        // Making a collection for the Residents including the new one
        Resident **temp = new Resident *[this->numOfResidents + 1];
        for (int i = 0; i < this->numOfResidents; i++)
        {
            temp[i] = this->residents[i];
        }
        delete[] this->residents;
        temp[this->numOfResidents] = resident;

        this->residents = temp;
        this->numOfResidents++;
    }
}

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
    case BuildingType::Old:
        return new Old(location);
    case BuildingType::Dormitory:
        return new Dormitory(location);
    default:
        throw std::invalid_argument("Invalid building type");
    }
}