#include <cstring>
#include <iostream>
#include <stdexcept>

#include "resident.hpp"
#include "building.hpp"

Resident::~Resident()
{
    delete[] this->name;
    this->name = nullptr;
}

bool Resident::operator==(const Resident &other) const
{
    // Id is different for every Resident
    if (this->id == other.id)
    {
        return true;
    }
    return false;
}

void Resident::print() const
{
    std::cout << "Name: " << this->name
              << "\nId: " << this->id
              << "\nProfession: ";
    this->printProfession();
    std::cout << "\nBuilding: " << this->getBuilding()->getType()
              << std::endl;
}

// Might throw std::invalid_argument
void Resident::printProfession() const
{
    switch (this->profession)
    {
    case Profession::Teacher:
        std::cout << "Teacher";
        break;
    case Profession::Programmer:
        std::cout << "Programmer";
        break;
    case Profession::Miner:
        std::cout << "Miner";
        break;
    case Profession::Unemployed:
        std::cout << "Unemployed";
        break;
    default:
        throw std::invalid_argument("Invalid Profession!");
        break;
    }
}

const char *Resident::getName() const
{
    return this->name;
}

unsigned Resident::getId() const
{
    return this->id;
}

Profession Resident::getProfession() const
{
    return this->profession;
}

const Building *Resident::getBuilding() const
{
    return this->building;
}

unsigned Resident::getHappiness() const
{
    return this->happiness;
}

unsigned Resident::getMoney() const
{
    return this->money;
}

unsigned Resident::getHealth() const
{
    return this->health;
}

void Resident::setBuilding(Building *building)
{
    this->building = building;
}

void Resident::setHappiness(unsigned happiness)
{
    this->happiness = happiness;
}

void Resident::setMoney(unsigned money)
{
    this->money = money;
}

void Resident::setHealth(unsigned health)
{
    this->health = health;
}

// Might throw std::bad_alloc or std::invalid_argument
Resident *Factory(const char *name, unsigned id, Profession profession)
{
    switch (profession)
    {
    case Profession::Teacher:
        return new Teacher(name, id);
        break;
    case Profession::Programmer:
        return new Programmer(name, id);
        break;
    case Profession::Miner:
        return new Miner(name, id);
        break;
    case Profession::Unemployed:
        return new Unemployed(name, id);
        break;
    }
}