#include <iostream>
#include <random>
#include <stdexcept>

#include "city.hpp"

#include "building.hpp"
#include "resident.hpp"

City::City(unsigned length, unsigned width, Date date)
    : length(length), width(width), startDate(date), currentDate(date), centerPoint(length / 2, width / 2)
{
    // Cannot have a City without Buildings or with 101x101 size
    if (length == 0 || width == 0 ||
        length > 100 || width > 100)
    {
        throw std::invalid_argument("Invalid size of City!");
    }

    this->buildings = new Building **[width];

    // Generate random BuildingType
    // Algorithm taken from StackOverflow
    // <the same one as the random income generator>
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);
    // End of algorithm

    for (int i = 0; i < width; i++)
    {
        this->buildings[i] = new (std::nothrow) Building *[length];
        if (!this->buildings[i])
        {
            clearBuildings(length, i);
            throw std::bad_alloc();
        }

        for (int j = 0; j < length; j++)
        {
            Location location(i, j);

            int type = dist(gen);
            switch (type)
            {
            case 0:
                buildings[i][j] = Factory(BuildingType::Modern, location, this->centerPoint, this->length, this->width);
                break;
            case 1:
                buildings[i][j] = Factory(BuildingType::Old, location, this->centerPoint, this->length, this->width);
                break;
            case 2:
                buildings[i][j] = Factory(BuildingType::Dormitory, location, this->centerPoint, this->length, this->width);
                break;
            }
        }
    }
}

City::~City()
{
    this->clearBuildings(this->length, this->width);
}

// Might throw std::invalid_argument or std::bad_alloc
void City::addResident(Resident *resident, Location location) const
{
    if (location.x >= this->length - 1 || location.y >= this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    this->buildings[location.y][location.x]->addResident(resident);
}

void City::removeResident(Resident *resident, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    this->buildings[location.y][location.x]->removeResident(resident);
}

bool City::checkResident(Resident *resident, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    this->buildings[location.y][location.x]->checkResident(resident);
}

int City::checkResidentPosition(Resident *resident, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    return this->buildings[location.y][location.x]->checkResidentPosition(resident);
}

void City::passOneDay(Date &currentDate) const
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->length; j++)
        {
            if (this->buildings[i][j] == nullptr)
            {
                // The program would crash if the Building is nullptr,
                // that's why we throw an exception
                throw std::invalid_argument("Building does not exist!");
            }

            this->buildings[i][j]->passOneDay(currentDate);
        }
    }
}

void City::passMultipleDays(Date &currentDate, unsigned days) const
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->length; j++)
        {
            if (this->buildings[i][j] == nullptr)
            {
                // The program would crash if the Building is nullptr,
                // that's why we throw an exception
                throw std::invalid_argument("Building does not exist!");
            }

            this->buildings[i][j]->passMultipleDays(currentDate, days);
        }
    }
}

void City::print() const
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->length; j++)
        {
            Location buildingLoc(j, i);
            this->printBuilding(buildingLoc);
        }
    }
}

void City::printBuilding(Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        std::cerr << "Building is outside of the City!" << std::endl;
    }
    else
    {
        std::cout << "\n Building <" << location.x << ", " << location.y << ">" << std::endl;
        this->buildings[location.y][location.x]->print();
    }
}

void City::printResident(const char *name, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        std::cerr << "Resident is outside of the City!" << std::endl;
        return;
    }

    int index = this->buildings[location.y][location.x]->checkResidentPosition(name);
    if (index == -1)
    {
        std::cerr << "No such Resident in Building!" << std::endl;
    }
    else
    {
        this->buildings[location.y][location.x]->getResident(name)->printStatus();
        this->buildings[location.y][location.x]->getResident(name)->printCharacteristics();
    }
}

unsigned City::getLength() const
{
    return this->length;
}

unsigned City::getWidth() const
{
    return this->width;
}

Location City::getCenterPoint() const
{
    return this->centerPoint;
}

const Building *City::getBuilding(Location location) const
{
    return this->buildings[location.y][location.x];
}

Date City::getStartDate() const
{
    return this->startDate;
}

Date City::getCurrentDate() const
{
    return this->currentDate;
}

void City::clearBuildings(unsigned length, unsigned width)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            delete this->buildings[i][j];
            this->buildings[i][j] = nullptr;
        }
        delete this->buildings[i];
        this->buildings[i] = nullptr;
    }
    delete[] this->buildings;
    this->buildings = nullptr;
}