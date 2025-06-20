#include <cstring>
#include <fstream>
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
            this->clearBuildings(length, i);
            throw std::bad_alloc();
        }

        for (int j = 0; j < length; j++)
        {
            Location location(i, j);

            int type = dist(gen);
            switch (type)
            {
            case 0:
                buildings[i][j] = Building::Factory(BuildingType::Modern, location, this->centerPoint, this->length, this->width);
                break;
            case 1:
                buildings[i][j] = Building::Factory(BuildingType::Old, location, this->centerPoint, this->length, this->width);
                break;
            case 2:
                buildings[i][j] = Building::Factory(BuildingType::Dormitory, location, this->centerPoint, this->length, this->width);
                break;
            }
        }
    }

    this->autoSave();
}

City::~City()
{
    this->clearBuildings(this->length, this->width);

    std::ofstream file("data.bin", std::ios::binary | std::ios_base::trunc);
    file.close();
}

void City::saveToFile(const char *fileName) const
{
    if (strcmp(fileName, "data.bin") == 0)
    {
        std::cerr << "File name already taken! Please choose another one!" << std::endl;
        return;
    }

    std::ofstream save(fileName, std::ios::binary);
    if (!save.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }
    std::ifstream load("data.bin", std::ios::binary);
    if (!load.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    // Copy the entire content of the temporary "data.bin" onto the permanent save file
    save << load.rdbuf();

    save.close();
    load.close();
}

City *City::loadFromFile(const char *fileName)
{
    std::ifstream load(fileName, std::ios::binary);
    if (!load.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    load.seekg(0, std::ios_base::end);
    unsigned sizeOfFile = load.tellg();

    if (sizeOfFile < sizeof(unsigned))
    {
        load.close();
        throw std::ios_base::failure("File reading error!");
    }

    int size;
    load.seekg(-sizeof(unsigned), std::ios_base::end);
    load.read((char *)&size, sizeof(unsigned));
    size += sizeof(unsigned);

    if (sizeOfFile < size)
    {
        load.close();
        throw std::ios_base::failure("File reading error!");
    }

    load.seekg(0, std::ios_base::end);
    load.seekg(-(size), std::ios_base::cur);

    unsigned length, width;
    Date startDate(1, 1, 2020), currentDate(1, 1, 2020);

    load.read((char *)&length, sizeof(unsigned));
    load.read((char *)&width, sizeof(unsigned));
    load.read((char *)&startDate, sizeof(Date));
    load.read((char *)&currentDate, sizeof(Date));

    City *city = new City(length, width, startDate, currentDate);

    city->buildings = new Building **[city->width];

    BuildingType type;
    Location location(0, 0);
    LocationType locationType;
    unsigned numOfResidents;

    for (int i = 0; i < width; i++)
    {
        city->buildings[i] = new (std::nothrow) Building *[length];
        if (!city->buildings[i])
        {
            city->clearBuildings(length, i);
            throw std::bad_alloc();
        }
        for (int j = 0; j < length; j++)
        {
            load.read((char *)&type, sizeof(BuildingType));
            load.read((char *)&location, sizeof(Location));
            load.read((char *)&locationType, sizeof(LocationType));
            load.read((char *)&numOfResidents, sizeof(unsigned));
            city->buildings[i][j] = Building::loadFromFile(load, type, location, locationType, numOfResidents);
        }
    }

    std::ofstream data("data.bin", std::ios::binary | std::ios::trunc);

    load.seekg(0, std::ios_base::beg);
    data << load.rdbuf();

    data.close();
    load.close();

    return city;
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

void City::addResident(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health, Location location)
{
    if (location.x >= this->length || location.y >= this->width)
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

    Resident *resident = Resident::Factory(name, profession, happiness, money, health);

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

void City::removeResident(const char *name, Location location) const
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
    this->buildings[location.y][location.x]->removeResident(name);
}

bool City::checkResident(Resident *resident, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return false;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    return this->buildings[location.y][location.x]->checkResident(resident);
}

bool City::checkResident(const char *name, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return false;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    return this->buildings[location.y][location.x]->checkResident(name);
}

// Might return -1 if Resident is not in the Building
int City::checkResidentPosition(Resident *resident, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return -1;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    return this->buildings[location.y][location.x]->checkResidentPosition(resident);
}

// Might return -1 if Resident is not in the Building
int City::checkResidentPosition(const char *name, Location location) const
{
    if (location.x > this->length || location.y > this->width)
    {
        // The user can correct themself
        std::cerr << "Building is outside of the city!" << std::endl;
        return -1;
    }
    if (this->buildings[location.y][location.x] == nullptr)
    {
        // The program would crash if the Building is nullptr,
        // that's why we throw an exception
        throw std::invalid_argument("Building does not exist!");
    }
    return this->buildings[location.y][location.x]->checkResidentPosition(name);
}

void City::passOneDay()
{
    this->currentDate.passOneDay();
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
            this->buildings[i][j]->passOneDay(this->currentDate);
        }
    }

    this->removeNotAliveResidents();
    this->autoSave();
}

void City::passMultipleDays(unsigned days)
{
    if (days == 0)
    {
        return;
    }
    for (int i = 0; i < days; i++)
    {
        this->passOneDay();
    }
}

void City::removeNotAliveResidents() const
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->length; j++)
        {
            this->buildings[i][j]->removeNotAliveResidents();
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
    if (location.x >= this->length || location.y >= this->width)
    {
        std::cerr << "Building is outside of the City!" << std::endl;
    }
    else
    {
        std::cout << "\nBuilding <" << location.x << ", " << location.y << ">" << std::endl;
        this->buildings[location.y][location.x]->print();
    }
}

void City::printResident(const char *name, Location location) const
{
    if (location.x >= this->length || location.y >= this->width)
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

City::City(unsigned length, unsigned width, Date startingDate, Date currentDate)
    : length(length), width(width), startDate(startDate), currentDate(currentDate), centerPoint(length / 2, width / 2)
{
    // Cannot have a City without Buildings or with 101x101 size
    if (length == 0 || width == 0 ||
        length > 100 || width > 100)
    {
        throw std::invalid_argument("Invalid size of City!");
    }
}

// Might throw std::ios_base::failure
void City::autoSave() const
{
    unsigned size = 0;

    std::ofstream save("data.bin", std::ios::binary | std::ios_base::app);
    if (!save.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    save.write((const char *)&this->length, sizeof(unsigned));
    size += sizeof(unsigned);
    save.write((const char *)&this->width, sizeof(unsigned));
    size += sizeof(unsigned);
    save.write((const char *)&this->startDate, sizeof(Date));
    size += sizeof(Date);
    save.write((const char *)&this->currentDate, sizeof(Date));
    size += sizeof(Date);

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->length; j++)
        {
            if (this->buildings[i][j] == nullptr)
            {
                throw std::invalid_argument("Building does not exist!");
            }
            this->buildings[i][j]->autoSave(save, size);
        }
    }

    save.write((const char *)&size, sizeof(unsigned));

    save.close();
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