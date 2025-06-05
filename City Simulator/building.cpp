#include <cstring>
#include <iostream>
#include <stdexcept>

#include "building.hpp"
#include "dormitory.hpp"
#include "modern.hpp"
#include "old.hpp"

#include "resident.hpp"

Building::~Building()
{
    delete[] this->residents;
    this->residents = nullptr;
}

// Might throw std::invalid_argument or std::bad_alloc
void Building::addResident(Resident *resident)
{
    if (this->numOfResidents == this->capacity)
    {
        throw std::invalid_argument("Building is full!");
    }
    if (resident->getBuilding() != nullptr &&
        resident->getBuilding()->checkResident(resident))
    {
        throw std::invalid_argument("Resident is still living in another Building!");
    }

    if (this->numOfResidents == 0)
    {
        // Create a new array with one pointer, pointing to the new Resident
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
            // Copying the pointers
            temp[i] = this->residents[i];
        }
        // Deleting the old pointers
        delete[] this->residents;
        // Assigning the pointer to the new Resident
        temp[this->numOfResidents] = resident;

        // Making this->residents to point to the temp array
        this->residents = temp;
        this->numOfResidents++;
    }
    // Make the Resident know his Building
    resident->setBuilding(this);
}

// Might throw std::invalid_argument or std::bad_alloc
void Building::removeResident(Resident *resident)
{
    int index = this->checkResidentPosition(resident);
    if (index == -1) // Check if the Resident is in the building
    {
        throw std::invalid_argument("Resident is not in the Building!");
    }

    // New collection without the removed Resident
    Resident **temp = new Resident *[this->numOfResidents - 1];
    for (int i = 0; i < index; i++)
    {
        // Assigning everyone before the removed one
        temp[i] = this->residents[i];
    }
    for (int i = index; i < this->numOfResidents - 1; i++)
    {
        // Assigning everyone after the removed one
        temp[i] = this->residents[i + 1];
    }
    // Removing the old pointers
    delete[] this->residents;
    // Assigning this->residents to the corrected collection
    this->residents = temp;
    this->numOfResidents--;

    // Remove the Building from the Resident
    resident->setBuilding(nullptr);
}

bool Building::checkResident(const Resident *resident) const
{
    if (this->numOfResidents == 0)
    {
        return false;
    }
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (this->residents[i] == resident)
        {
            return true;
        }
    }
    return false;
}

bool Building::checkResident(const char *name) const
{
    if (this->numOfResidents == 0)
    {
        return false;
    }
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (strcmp(this->residents[i]->getName(), name) == 0)
        {
            return true;
        }
    }
    return false;
}

// Returns -1 if there is no such Resident
int Building::checkResidentPosition(const Resident *resident) const
{
    if (this->numOfResidents == 0)
    {
        return -1;
    }
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (this->residents[i] == resident)
        {
            return i;
        }
    }
    return -1;
}

// Returns -1 if there is no such Resident
int Building::checkResidentPosition(const char *name) const
{
    if (this->numOfResidents == 0)
    {
        return -1;
    }
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (strcmp(this->residents[i]->getName(), name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Combining all the other printing methods
void Building::print() const
{
    this->printStatus();

    if (this->numOfResidents == 0)
    {
        std::cout << "<No Residents in Building>" << std::endl;
    }
    else
    {
        for (int i = 0; i < this->numOfResidents; i++)
        {
            std::cout << "\t";
            this->residents[i]->printStatus();
            this->residents[i]->printCharacteristics();
        }
    }
}

void Building::printStatus() const
{
    std::cout << "Building type: " << this->getType()
              << "\nRent: " << this->getRent()
              << "\nResidents: " << this->getNumOfResidents()
              << std::endl;
}

double Building::getRent() const
{
    return this->rent;
}

Location Building::getLocation() const
{
    return this->location;
}

LocationType Building::getLocationType() const
{
    return this->locationType;
}

const Resident *Building::getResident(const char *name) const
{
    int index = this->checkResidentPosition(name);

    if (index == -1)
    {
        throw std::invalid_argument("Resident is not in the Building!");
    }

    return this->residents[index];
}

unsigned Building::getNumOfResidents() const
{
    return this->numOfResidents;
}

Building::Building(Location location)
    : location(location.x, location.y) {}

void Building::setRent(double rent)
{
    this->rent = rent;
}

void Building::setLocationType(LocationType locationType)
{
    this->locationType = locationType;
}

void Building::setCapacity(unsigned capacity)
{
    this->capacity = capacity;
}

// Might throw std::bad_alloc or std::invalid_argument
Building *Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned length, unsigned width)
{
    switch (buildingType)
    {
    case BuildingType::Modern:
        return new Modern(location, centerPoint, length, width);
        break;
    case BuildingType::Old:
        return new Old(location, centerPoint, length, width);
        break;
    case BuildingType::Dormitory:
        return new Dormitory(location, centerPoint, length, width);
        break;
    default:
        throw std::invalid_argument("Invalid building type");
        break;
    }
}