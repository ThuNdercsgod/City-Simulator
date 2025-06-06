#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>

#include "resident.hpp"
#include "teacher.hpp"
#include "programmer.hpp"
#include "miner.hpp"
#include "unemployed.hpp"

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

// Location and position needed to create a unique id
// Might throw std::invalid_argument or std::bad_alloc
Resident *Resident::createRandomResident(Location location, unsigned position) const
{
    // Generate random Resident profession
    // Algorithm taken from StackOverflow
    // <the same one as the random income generator>
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    // End of algorithm

    unsigned profession = dist(gen);
    const char *name = this->createRandomName();
    unsigned id = location.x * 10000 + location.y * 100 + position;

    switch (profession)
    {
    case 0:
        return Factory(name, id, Profession::Teacher);
        break;
    case 1:
        return Factory(name, id, Profession::Programmer);
        break;
    case 2:
        return Factory(name, id, Profession::Miner);
        break;
    case 3:
        return Factory(name, id, Profession::Unemployed);
        break;
    default:
        throw std::invalid_argument("Invalid Profession for Random Resident!");
        break;
    }
}

void Resident::print() const
{
    this->printStatus();
    this->printCharacteristics();

    std::cout << "Profession: " << this->getProfession()
              << "\nBuilding: ";

    if (this->building != nullptr)
    {
        std::cout << this->getBuilding()->getType();
    }
    else
    {
        std::cout << "<No Building>";
    }

    std::cout << std::endl;
}

void Resident::printStatus() const
{
    std::cout << "Name: " << this->name
              << "\nId: " << this->id
              << std::endl;
}

void Resident::printCharacteristics() const
{
    std::cout << "Happiness: " << this->happiness
              << "\nMoney: " << this->money
              << "\nHealth: " << this->health
              << std::endl;
}

const char *Resident::getName() const
{
    return this->name;
}

unsigned Resident::getId() const
{
    return this->id;
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

bool Resident::getIsAlive() const
{
    return this->isAlive;
}

void Resident::setBuilding(Building *building)
{
    this->building = building;
}

// Might throw std::invalid_argument or std::bad_alloc
Resident::Resident(const char *name, unsigned id)
    : id(id)
{
    if (name == nullptr ||
        strcmp(name, "") == 0)
    {
        throw std::invalid_argument("Ivalid name for Resident!");
    }

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Pick a random name form an already existing list
const char *Resident::createRandomName() const
{
    static const char *names[20] = {
        "Gosho",
        "Misho",
        "Marti",
        "Marto",
        "Nicki",
        "Mayya",
        "Jorro",
        "Aycha",
        "Yulli",
        "Kremi",
        "Ketti",
        "Katti",
        "Georg",
        "Kriss",
        "Bobbi",
        "Ivann",
        "Mitko",
        "Radda",
        "Maria",
        "Vladi"};

    // Generate random Name position
    // Algorithm taken from StackOverflow
    // <the same one as the random income generator>
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 19);
    // End of algorithm

    return names[dist(gen)];
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

void Resident::setIsAlive(bool alive)
{
    this->isAlive = alive;
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
    default:
        throw std::invalid_argument("Invalid Profession!");
        break;
    }
}