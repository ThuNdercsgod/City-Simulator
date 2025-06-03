#include <cstring>
#include <stdexcept>

#include "building.hpp"
#include "resident.hpp"
#include "test.hpp"

void BuildingTest::basic()
{
    Location location(0, 0);
    Location center(5, 5);
    Building *modern = Factory(BuildingType::Modern, location, center, 10, 10);

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
    Building *modern = Factory(BuildingType::Modern, location, center, 10, 10);
    modern->printStatus();

    Resident *teacher = Factory("Teacher", 1, Profession::Teacher);

    modern->addResident(teacher);

    modern->print();

    modern->removeResident(teacher);

    modern->print();

    delete modern;
    delete teacher;
}

void ResidentTest::basic()
{
    Resident *teacher = Factory("Teacher", 1, Profession::Teacher);

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
    Resident *teacher = Factory("Teacher", 1, Profession::Teacher);
    unsigned dayInSim = 1;

    teacher->print();
    teacher->passOneDay(dayInSim);
    teacher->print();

    teacher->passMultipleDays(30, dayInSim);
    if (teacher->getIsAlive())
    {
        teacher->print();
    }

    delete teacher;
}