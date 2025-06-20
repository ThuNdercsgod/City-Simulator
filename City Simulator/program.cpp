#include <cstring>
#include <iostream>
#include <stdexcept>

#include "building.hpp"
#include "city.hpp"
#include "program.hpp"
#include "resident.hpp"

// Might throw std::bad_alloc
City *Program::generate()
{
    City *city;
    Date date(1, 1, 2020);

    int length = -1, width = -1;
    std::cout << "Enter <length> <width>:" << std::endl;
    std::cin >> length >> width;

    if (length == -1 || width == -1 ||
        length <= 0 || width <= 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        return nullptr;
    }

    city = new City(length, width, date);

    std::cout << "Date: " << city->getCurrentDate().getDay()
              << "." << city->getCurrentDate().getMonth()
              << "." << city->getCurrentDate().getYear()
              << std::endl;
    return city;
}

void Program::addResident(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        std::cout << "Failed" << std::endl;
        return;
    }

    char name[16];
    int x = -1, y = -1;
    char professionText[32];
    int happiness = -1, money = -1, health = -1;

    std::cout << "Enter <location x> <location y> <name> <profession> <happiness> <money> <health>:" << std::endl;
    std::cin >> x >> y >> name >> professionText >> happiness >> money >> health;

    if (x == -1 || y == -1 || happiness == -1 || money == -1 || health == -1 ||
        x < 0 || y < 0 || happiness < 0 || money < 0 || health < 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        std::cout << "Failed" << std::endl;
        return;
    }

    Profession profession;
    if (strcmp(professionText, "Teacher") == 0)
    {
        profession = Profession::Teacher;
    }
    else if (strcmp(professionText, "Programmer") == 0)
    {
        profession = Profession::Programmer;
    }
    else if (strcmp(professionText, "Miner") == 0)
    {
        profession = Profession::Miner;
    }
    else if (strcmp(professionText, "Unemployed") == 0)
    {
        profession = Profession::Unemployed;
    }
    else
    {
        std::cerr << "Invalid Command!" << std::endl;
        std::cout << "Failed" << std::endl;
        return;
    }

    Location location(x, y);

    if (city->checkResident(name, location))
    {
        std::cerr << "Resident already exists!" << std::endl;
        std::cout << "Failed" << std::endl;
        return;
    }

    city->addResident(name, profession, happiness, money, health, location);

    if (city->checkResident(name, location))
    {
        std::cout << "Completed!" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }
}

void Program::removeResident(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    char name[16];
    int x = -1, y = -1;

    std::cout << "Enter <location x> <location y> <name>:" << std::endl;
    std::cin >> x >> y >> name;

    if (x == -1 || y == -1 ||
        x < 0 || y < 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        std::cout << "Failed" << std::endl;
        return;
    }

    Location location(x, y);

    city->removeResident(name, location);

    if (!city->checkResident(name, location))
    {
        std::cout << "Completed!" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }
}

void Program::stepOne(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    city->passOneDay();
}

void Program::stepMultiple(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    int days;

    std::cout << "Enter <days>:" << std::endl;
    std::cin >> days;

    if (days == 0)
    {
        return;
    }
    else if (days < 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        return;
    }

    city->passMultipleDays(days);
}

void Program::info(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }
    std::cout << "Date: " << city->getCurrentDate().getDay()
              << "." << city->getCurrentDate().getMonth()
              << "." << city->getCurrentDate().getYear()
              << std::endl;
    city->print();
}

void Program::infoBuilding(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    int x = -1, y = -1;

    std::cout << "Enter <location x> <location y>:" << std::endl;
    std::cin >> x >> y;

    if (x == -1 || y == -1 ||
        x < 0 || y < 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        return;
    }

    Location location(x, y);

    city->printBuilding(location);
}

void Program::infoResident(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    int x = -1, y = -1;
    char name[16];

    std::cout << "Enter <location x> <location y> <name>:" << std::endl;
    std::cin >> x >> y >> name;

    if (x == -1 || y == -1 ||
        x < 0 || y < 0)
    {
        std::cerr << "Invalid command!" << std::endl;
        return;
    }

    Location location(x, y);

    city->printResident(name, location);
}

void Program::saveToFile(City *city)
{
    if (city == nullptr)
    {
        std::cerr << "City is not yet created!" << std::endl;
        return;
    }

    char fileName[64];
    std::cout << "Enter <file name>:" << std::endl;
    std::cin >> fileName;

    city->saveToFile(fileName);
}

City *Program::loadFromFile()
{
    City *city = nullptr;

    char fileName[64];
    std::cout << "Enter <file name>:" << std::endl;
    std::cin >> fileName;

    city = City::loadFromFile(fileName);

    return city;
}

void Test::BuildingTest::basic()
{
    Location location(0, 0);
    Location center(5, 5);
    Building *modern = Building::Factory(BuildingType::Modern, location, center, 10, 10);

    if (strcmp(modern->getType(), "Modern") != 0 ||
        modern->getNumOfResidents() != 0)
    {
        delete modern;
        throw std::invalid_argument("Invalid Modern Building!");
    }

    modern->printStatus();

    delete modern;
}

void Test::BuildingTest::residents()
{
    Location location(0, 0);
    Location center(5, 5);
    Building *modern = Building::Factory(BuildingType::Modern, location, center, 10, 10);
    modern->printStatus();

    Resident *teacher = Resident::Factory("Teacher", Profession::Teacher);

    modern->addResident(teacher);

    modern->print();

    modern->removeResident(teacher);

    modern->print();

    delete modern;
    delete teacher;
}

void Test::ResidentTest::basic()
{
    Resident *teacher = Resident::Factory("Teacher", Profession::Teacher);

    if (strcmp(teacher->getProfession(), "Teacher") != 0 ||
        teacher->getBuilding() != nullptr)
    {
        delete teacher;
        throw std::invalid_argument("Invalid Teacher!");
    }

    teacher->print();

    delete teacher;
}

void Test::ResidentTest::passDays()
{
    Resident *teacher = Resident::Factory("Teacher", Profession::Teacher);
    Date date(1, 1, 2000);

    teacher->print();
    teacher->passOneDay(date);
    teacher->print();

    teacher->passMultipleDays(date, 31);
    if (teacher->getIsAlive())
    {
        teacher->print();
    }

    delete teacher;
}

void Test::CityTest::basic()
{
    Date date(7, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);
}

void Test::CityTest::passDays()
{
    Date date(9, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);

    city.passOneDay();
    city.printBuilding(location);

    city.passMultipleDays(30);
    city.printBuilding(location);
}

void Test::CityTest::resident()
{
    Date date(9, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);

    Resident *resident = Resident::Factory("Hello", Profession::Teacher);

    city.addResident(resident, location);
    city.printBuilding(location);

    city.removeResident(resident->getName(), location);
    city.printBuilding(location);
}

void Test::SimulationTest::generate()
{
    City *city = nullptr;
    city = Program::generate();

    if (city == nullptr)
    {
        std::cout << "Generating failed!" << std::endl;
    }
    else
    {
        std::cout << "Generating successful!" << std::endl;
    }

    Program::info(city);

    delete city;
    city = nullptr;
}