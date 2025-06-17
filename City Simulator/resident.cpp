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

// Might throw std::bad_alloc or std::invalid_argument
Resident *Resident::Factory(const char *name, Profession profession)
{
    switch (profession)
    {
    case Profession::Teacher:
        return new Teacher(name);
        break;
    case Profession::Programmer:
        return new Programmer(name);
        break;
    case Profession::Miner:
        return new Miner(name);
        break;
    case Profession::Unemployed:
        return new Unemployed(name);
        break;
    default:
        throw std::invalid_argument("Invalid Profession!");
        break;
    }
}

// Might throw std::bad_alloc or std::invalid_argument
Resident *Resident::Factory(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health)
{
    switch (profession)
    {
    case Profession::Teacher:
        return new Teacher(name, happiness, money, health);
        break;
    case Profession::Programmer:
        return new Programmer(name, happiness, money, health);
        break;
    case Profession::Miner:
        return new Miner(name, happiness, money, health);
        break;
    case Profession::Unemployed:
        return new Unemployed(name, happiness, money, health);
        break;
    default:
        throw std::invalid_argument("Invalid Profession!");
        break;
    }
}

void Resident::saveToFile(std::ofstream &save) const
{
    if (!save.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    if (strcmp(this->getProfession(), "Teacher") == 0)
    {
        Profession profession = Profession::Teacher;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Programmer") == 0)
    {
        Profession profession = Profession::Programmer;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Miner") == 0)
    {
        Profession profession = Profession::Miner;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Unemployed") == 0)
    {
        Profession profession = Profession::Unemployed;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else
    {
        throw std::invalid_argument("Invalid Resident profession!");
    }
    unsigned nameSize = strlen(this->name);
    save.write((const char *)&nameSize, sizeof(unsigned));
    save.write(this->name, nameSize);
    save.write((const char *)&this->happiness, sizeof(unsigned));
    save.write((const char *)&this->money, sizeof(unsigned));
    save.write((const char *)&this->health, sizeof(unsigned));
}

void Resident::autoSave(std::ofstream &save, unsigned &size) const
{
    if (!save.is_open())
    {
        throw std::ios_base::failure("File opening error!");
    }

    if (strcmp(this->getProfession(), "Teacher") == 0)
    {
        Profession profession = Profession::Teacher;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Programmer") == 0)
    {
        Profession profession = Profession::Programmer;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Miner") == 0)
    {
        Profession profession = Profession::Miner;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else if (strcmp(this->getProfession(), "Unemployed") == 0)
    {
        Profession profession = Profession::Unemployed;
        save.write((const char *)&profession, sizeof(Profession));
    }
    else
    {
        throw std::invalid_argument("Invalid Resident profession!");
    }
    size += sizeof(Profession);
    unsigned nameSize = strlen(this->name);
    save.write((const char *)&nameSize, sizeof(unsigned));
    size += sizeof(unsigned);
    save.write(this->name, nameSize);
    size += nameSize;
    save.write((const char *)&this->happiness, sizeof(unsigned));
    size += sizeof(unsigned);
    save.write((const char *)&this->money, sizeof(unsigned));
    size += sizeof(unsigned);
    save.write((const char *)&this->health, sizeof(unsigned));
    size += sizeof(unsigned);
}

// Location and position needed to create a unique id
// Might throw std::invalid_argument or std::bad_alloc
Resident *Resident::createRandomResident(Location location, unsigned position)
{
    // Generate random Resident profession
    // Algorithm taken from StackOverflow
    // <the same one as the random income generator>
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);
    // End of algorithm

    unsigned profession = dist(gen);
    const char *name = Resident::createRandomName();
    unsigned id = location.x * 10000 + location.y * 100 + position;

    switch (profession)
    {
    case 0:
        return Resident::Factory(name, Profession::Teacher);
        break;
    case 1:
        return Resident::Factory(name, Profession::Programmer);
        break;
    case 2:
        return Resident::Factory(name, Profession::Miner);
        break;
    case 3:
        return Resident::Factory(name, Profession::Unemployed);
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

    std::cout << "\n\t\tBuilding: ";

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
    std::cout << "\tName: " << this->name
              << "\n\t\tProfession: " << this->getProfession()
              << std::endl;
}

void Resident::printCharacteristics() const
{
    std::cout << "\t\tHappiness: " << this->happiness
              << "\n\t\tMoney: " << this->money
              << "\n\t\tHealth: " << this->health
              << std::endl;
}

const char *Resident::getName() const
{
    return this->name;
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
Resident::Resident(const char *name)
{
    if (name == nullptr ||
        strcmp(name, "") == 0)
    {
        throw std::invalid_argument("Ivalid name for Resident!");
    }

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Might throw std::invalid_argument or std::bad_alloc
Resident::Resident(const char *name, unsigned happiness, unsigned money, unsigned health)
    : happiness(happiness), money(money), health(health)
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
const char *Resident::createRandomName()
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