#include <cstring>
#include <iostream>
#include <stdexcept>

#include "building.hpp"
#include "city.hpp"
#include "resident.hpp"
#include "test.hpp"

void BuildingTest::basic()
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

void BuildingTest::residents()
{
    Location location(0, 0);
    Location center(5, 5);
    Building *modern = Building::Factory(BuildingType::Modern, location, center, 10, 10);
    modern->printStatus();

    Resident *teacher = Resident::Factory("Teacher", 1, Profession::Teacher);

    modern->addResident(teacher);

    modern->print();

    modern->removeResident(teacher);

    modern->print();

    delete modern;
    delete teacher;
}

void ResidentTest::basic()
{
    Resident *teacher = Resident::Factory("Teacher", 1, Profession::Teacher);

    if (strcmp(teacher->getProfession(), "Teacher") != 0 ||
        teacher->getBuilding() != nullptr)
    {
        delete teacher;
        throw std::invalid_argument("Invalid Teacher!");
    }

    teacher->print();

    delete teacher;
}

void ResidentTest::passDays()
{
    Resident *teacher = Resident::Factory("Teacher", 1, Profession::Teacher);
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

void CityTest::basic()
{
    Date date(7, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);
}

void CityTest::passDays()
{
    Date date(9, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);

    city.passOneDay(date);
    city.printBuilding(location);

    city.passMultipleDays(date, 30);
    city.printBuilding(location);
}

void CityTest::resident()
{
    Date date(9, 6, 2025);
    City city(3, 3, date);

    Location location(0, 0);
    city.printBuilding(location);

    Resident *resident = Resident::Factory("Hello", 12345, Profession::Teacher);

    city.addResident(resident, location);
    city.printBuilding(location);

    city.removeResident(resident->getName(), location);
    city.printBuilding(location);
}