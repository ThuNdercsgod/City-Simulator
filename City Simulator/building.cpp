#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>

#include "building.hpp"
#include "dormitory.hpp"
#include "modern.hpp"
#include "old.hpp"

#include "resident.hpp"

Building::~Building()
{
    for (int i = 0; i < this->numOfResidents; i++)
    {
        delete this->residents[i];
        this->residents[i] = nullptr;
    }
    delete[] this->residents;
    this->residents = nullptr;
}

void Building::saveToFile(std::ofstream &save) const
{
    if (!save.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    if (strcmp(this->getType(), "Modern") == 0)
    {
        BuildingType type = BuildingType::Modern;
        save.write((const char *)&type, sizeof(BuildingType));
    }
    else if (strcmp(this->getType(), "Old") == 0)
    {
        BuildingType type = BuildingType::Old;
        save.write((const char *)&type, sizeof(BuildingType));
    }
    else if (strcmp(this->getType(), "Dormitory") == 0)
    {
        BuildingType type = BuildingType::Dormitory;
        save.write((const char *)&type, sizeof(BuildingType));
    }
    else
    {
        throw std::invalid_argument("Invalid building type");
    }
    save.write((const char *)&this->location, sizeof(Location));
    save.write((const char *)&this->locationType, sizeof(LocationType));
    save.write((const char *)&this->numOfResidents, sizeof(unsigned));

    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (this->residents[i] == nullptr)
        {
            throw std::invalid_argument("Resident does not exist!");
        }
        this->residents[i]->saveToFile(save);
    }
}

Building *Building::loadFromFile(std::ifstream &load, BuildingType buildingType, Location location, LocationType locationType, unsigned numOfResidents)
{
    switch (buildingType)
    {
    case BuildingType::Modern:
        return new Modern(load, location, locationType, numOfResidents);
        break;
    case BuildingType::Old:
        return new Old(load, location, locationType, numOfResidents);
        break;
    case BuildingType::Dormitory:
        return new Dormitory(load, location, locationType, numOfResidents);
        break;
    default:
        throw std::invalid_argument("Invalid building type");
        break;
    }
}

// Might throw std::bad_alloc or std::invalid_argument
Building *Building::Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned length, unsigned width)
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

// Might throw std::invalid_argument or std::bad_alloc
void Building::addResident(Resident *resident)
{
    if (resident == nullptr)
    {
    }
    if (this->numOfResidents == this->capacity)
    {
        std::cerr << "Building is full!" << std::endl;
        return;
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
        this->numOfResidents++;
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
    this->residents[this->numOfResidents - 1]->setBuilding(this);
}

// Might throw std::invalid_argument or std::bad_alloc
void Building::removeResident(Resident *resident)
{
    int index = this->checkResidentPosition(resident);
    if (index == -1) // Check if the Resident is in the building
    {
        std::cerr << "Resident is not in the Building!";
        return;
    }

    // New collection without the removed Resident
    Resident **temp = new Resident *[this->numOfResidents - 1];

    // Remove the Building from the Resident
    this->residents[index]->setBuilding(nullptr);

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
}

void Building::removeResident(const char *name)
{
    int index = this->checkResidentPosition(name);
    if (index == -1) // Check if the Resident is in the building
    {
        std::cerr << "Resident is not in the Building!";
        return;
    }

    // New collection without the removed Resident
    Resident **temp = new Resident *[this->numOfResidents - 1];

    // Remove the Building from the Resident
    this->residents[index]->setBuilding(nullptr);

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
}

bool Building::checkResident(const Resident *resident) const
{
    if (this->numOfResidents == 0)
    {
        return false;
    }
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (strcmp(this->residents[i]->getName(), resident->getName()) == 0)
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
        if (strcmp(this->residents[i]->getName(), resident->getName()) == 0)
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

void Building::passOneDay(Date &currentDate) const
{
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (this->residents[i] == nullptr)
        {
            throw std::invalid_argument("Resident does not exist!");
        }
        this->residents[i]->passOneDay(currentDate);
    }
}

void Building::passMultipleDays(Date &currentDate, unsigned days) const
{
    for (int i = 0; i < this->numOfResidents; i++)
    {
        if (this->residents[i] == nullptr)
        {
            throw std::invalid_argument("Resident does not exist!");
        }
        this->residents[i]->passMultipleDays(currentDate, days);
    }
}

void Building::removeNotAliveResidents()
{
    for (int i = numOfResidents - 1; i >= 0; i--)
    {
        if (this->residents[i]->getIsAlive() == false)
        {
            this->residents[i]->printStatus();
            std::cout << "\t\tBuilding: " << this->getType() << std::endl;
            this->removeResident(this->residents[i]);
        }
    }
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
            this->residents[i]->printStatus();
            this->residents[i]->printCharacteristics();
        }
    }
}

void Building::printStatus() const
{
    std::cout << "\tBuilding type: " << this->getType()
              << "\n\tRent: " << this->getRent()
              << "\n\tResidents: " << this->getNumOfResidents()
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

unsigned Building::getCapacity() const
{
    return this->capacity;
}

Building::Building(Location location)
    : location(location.x, location.y) {}

// Check only part of the Residents (not the whole array)
bool Building::checkName(const char *name, unsigned position) const
{
    for (int i = 0; i < position; i++)
    {
        if (strcmp(this->residents[i]->getName(), name) == 0)
        {
            return true;
        }
    }
    return false;
}

// Creates a random number of random Residents with random professions
// Might throw std::invalid_argument or std::bad_alloc
void Building::createRandomResidents()
{
    if (this->capacity == 0)
    {
        throw std::invalid_argument("Invalid capacity for Building!");
    }
    // Generate random number of Residents
    // Algorithm taken from StackOverflow
    // <the same one as the random income generator>
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, this->capacity);
    // End of algorithm

    this->numOfResidents = dist(gen);

    if (this->numOfResidents > this->capacity)
    {
        throw std::invalid_argument("Invalid number of Residents in Building!");
    }

    this->residents = new Resident *[this->numOfResidents];

    for (unsigned i = 0; i < this->numOfResidents; i++)
    {
        this->residents[i] = Resident::createRandomResident(this->location, i);
        // Check so every name is unique in the Building
        if (this->checkName(this->residents[i]->getName(), i))
        {
            delete this->residents[i];
            this->residents[i] = nullptr;
            i--;
        }
    }
}

void Building::setRent(double rent)
{
    this->rent = rent;
}

void Building::setLocationType(LocationType locationType)
{
    this->locationType = locationType;
}

void Building::setNumOfResidents(unsigned numOfResidents)
{
    if (numOfResidents > this->capacity)
    {
        throw std::invalid_argument("Invalid number of Residents in Building!");
    }
    this->numOfResidents = numOfResidents;
}

void Building::setCapacity(unsigned capacity)
{
    this->capacity = capacity;
}