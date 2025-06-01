#include <cstring>
#include <stdexcept>

#include "building.hpp"
#include "resident.hpp"
#include "test.hpp"

void BuildingTest::basic()
{
    Location location = Location::Normal;
    Building *modern = Factory(BuildingType::Modern, location);

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
    Location location = Location::Normal;
    Building *modern = Factory(BuildingType::Modern, location);
    modern->printStatus();

    Resident *teacher = Factory("Teacher", 1, Profession::Teacher);

    modern->addResident(teacher);

    modern->print();

    modern->removeResident(teacher);

    modern->print();

    delete modern;
    delete teacher;
}