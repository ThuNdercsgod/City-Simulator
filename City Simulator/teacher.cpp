#include <random>

#include "teacher.hpp"

#include "building.hpp"

Teacher::Teacher(const char *name, unsigned id)
    : Resident(name, id) {}

void Teacher::passOneDay(Date &currentDate)
{
    // Food
    if (this->getMoney() < 50)
    {
        this->setMoney(0);
        this->setHealth(0);
        this->setHappiness(0);
        this->setIsAlive(false);
        return;
    }
    else
    {
        this->setMoney(this->getMoney() - 50);
    }
    // Profession cost
    this->setHappiness(((this->getHappiness() + 1) < 100) ? (this->getHappiness() + 1) : 100);

    // The 1st day of every month
    if (currentDate.getDay() == 1)
    {
        // Generate random income between 1200 and 1300 for every month
        // Algorithm taken from StackOverflow
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1200, 1300);
        int income = dist(gen);
        // End of algorithm

        if (this->getBuilding() != nullptr &&
            this->getMoney() < this->getBuilding()->getRent())
        {
            this->setMoney(0);
            this->setHappiness(0);
        }
        else if (this->getBuilding() != nullptr)
        {
            this->setMoney(this->getMoney() + income - this->getBuilding()->getRent());
        }
        else
        {
            this->setMoney(this->getMoney() + income);
        }
    }

    if (this->getHappiness() == 0 &&
        this->getMoney() == 0 &&
        this->getHealth() == 0)
    {
        this->setIsAlive(false);
    }
}

void Teacher::passMultipleDays(Date &currentDate, unsigned days)
{
    if (days == 0)
    {
        return;
    }
    for (unsigned i = 0; i < days; i++)
    {
        if (this->getIsAlive() == false)
        {
            break;
        }
        this->passOneDay(currentDate);
    }
}

const char *Teacher::getProfession() const
{
    return "Teacher";
}