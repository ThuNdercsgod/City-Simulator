#include <cmath>
#include <stdexcept>

#include "dormitory.hpp"

#include "resident.hpp"

// Might throw std::invalid_argument or std::bad_alloc
Dormitory::Dormitory(Location location, Location centerPoint, unsigned length, unsigned width)
    : Building(location)
{
    float distanceFromCenter = sqrt((centerPoint.x - location.x) * (centerPoint.x - location.x) +
                                    (centerPoint.y - location.y) * (centerPoint.y - location.y));

    float min = (width < length) ? width : length;

    if (distanceFromCenter < (min / 8))
    {
        this->setLocationType(LocationType::Central);
        this->setRent(40 * 2.5);
    }
    else if (distanceFromCenter > (6 * min / 8))
    {
        this->setLocationType(LocationType::Outer);
        this->setRent(40 - (0.2 * 40));
    }
    else
    {
        this->setLocationType(LocationType::Normal);
        this->setRent(40);
    }

    this->setCapacity(5);
    this->createRandomResidents();
}

Dormitory::Dormitory(std::ifstream &load, Location location, LocationType locationType, unsigned numOfResidents)
    : Building(location)
{
    this->setCapacity(5);
    this->setLocationType(locationType);

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

    Profession profession;
    unsigned nameSize;
    char *name;
    unsigned happiness, money, health;

    for (int i = 0; i < numOfResidents; i++)
    {
        load.read((char *)&profession, sizeof(Profession));
        load.read((char *)&nameSize, sizeof(unsigned));
        if (nameSize == 0)
        {
            throw std::invalid_argument("Invalid Resident name size!");
        }

        name = new char[nameSize + 1];

        load.read(name, nameSize);
        load.read((char *)&happiness, sizeof(unsigned));
        load.read((char *)&money, sizeof(unsigned));
        load.read((char *)&health, sizeof(unsigned));
        addResident(Resident::Factory(name, profession, happiness, money, health));
        delete[] name;
    }
}

const char *Dormitory::getType() const
{
    return "Dormitory";
}