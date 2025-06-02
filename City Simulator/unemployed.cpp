#include "unemployed.hpp"

#include "building.hpp"

Unemployed::Unemployed(const char *name, unsigned id)
    : Resident(name, id) {}

void Unemployed::passOneDay(unsigned dayInSim)
{
    // Food
    if (this->getMoney() < 50)
    {
        this->setMoney(0);
        this->setHealth(0);
    }
    else
    {
        this->setMoney(this->getMoney() - 50);
    }
    // Profession cost
    this->setHappiness(((this->getHealth() - 1) >= 0) ? (this->getHealth() - 1) : 100);

    // The 1st day of every month
    if (dayInSim % 30 == 1)
    {
        int income = 0;

        if (this->getMoney() < this->getBuilding()->getRent())
        {
            this->setMoney(0);
            this->setHappiness(0);
        }
        else
        {
            this->setMoney(this->getMoney() + income - this->getBuilding()->getRent());
        }
    }

    if (this->getHappiness() == 0 &&
        this->getMoney() == 0 &&
        this->getHealth() == 0)
    {
        this->setIsAlive(false);
    }
}

void Unemployed::passMultipleDays(unsigned days, unsigned dayInSim)
{
    for (int i = 0; i < days; i++)
    {
        this->passOneDay(dayInSim + i);
    }
}

const char *Unemployed::getProfession() const
{
    return "Unemployed";
}